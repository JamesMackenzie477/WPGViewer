#include "Package.h"

#include <iostream>

using namespace std;

// updates a file in the package
BOOL Package::Update(LPCSTR lpName, PVOID pData, DWORD dwDataSize, DWORD dwAction)
{
	// gets the section associated with the file
	if (PPACKAGE_SECTION pSection = GetSection(lpName))
	{
		// calculates the new size of the package
		DWORD dwPackageSize = this->dwSize + (dwDataSize - pSection->DataSize);
		// checks if the data should be compressed
		if (dwAction & 0b1)
			// calculates the new size of the package
			dwPackageSize = this->dwSize + (compressBound(dwDataSize) - pSection->DataSize);
		// validates the size
		if (dwPackageSize > 0)
		{
			// creates a buffer to store the updated package
			if (PPACKAGE_HEADER pUpdatedPackage = (PPACKAGE_HEADER)VirtualAlloc(NULL, dwPackageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE))
			{
				// casts the pointer to a package header
				PPACKAGE_HEADER pHeader = (PPACKAGE_HEADER)pPackage;
				// writes the package header to the buffer
				*pUpdatedPackage = *pHeader;
				// casts the buffer into package sections
				PPACKAGE_SECTION pUpdatedSections = (PPACKAGE_SECTION)(pUpdatedPackage + 1);
				// writes the package sections to the buffer
				// gets the package sections array
				PPACKAGE_SECTION pSections = (PPACKAGE_SECTION)(pHeader + 1);
				// used to calculate the file size
				DWORD dwFileSize = sizeof(PACKAGE_HEADER) + (sizeof(PACKAGE_SECTION) * pHeader->NumberOfSections);
				// iterates through the package sections
				for (int i = 0; i < pHeader->NumberOfSections; i++)
				{
					// writes the package section to the buffer
					pUpdatedSections[i] = pSections[i];
					// if the package file name is the same as the one we want to replace
					if (_stricmp(pSections[i].FileName, lpName) == 0)
					{
						// updates the section header
						pUpdatedSections[i].DataInfo = dwAction;
						// checks if the file need compressing
						if (dwAction & 0b1)
						{
							// calculates the compressed size
							DWORD dwCompressed = compressBound(dwSize);
							// writes the decompressed size to the buffer
							*(DWORD*)((PBYTE)pUpdatedPackage + dwFileSize) = dwDataSize;
							// compresses the data to the file
							if (compress((PBYTE)pUpdatedPackage + dwFileSize + 4, &dwCompressed, (PBYTE)pData, dwDataSize) != Z_OK)
							{
								// fail
								return FALSE;
							}
							// sets the data size
							pUpdatedSections[i].DataSize = dwCompressed + 4;
							// updates the section header
							pUpdatedSections[i].DataOffset = dwFileSize;
							// calculates the file size
							dwFileSize += dwCompressed + 4;
						}
					}
					else
					{
						// writes the file data to the buffer
						memcpy((PBYTE)pUpdatedPackage + dwFileSize, (PBYTE)pPackage + pSections[i].DataOffset, pSections[i].DataSize);
						// updates the section header
						pUpdatedSections[i].DataOffset = dwFileSize;
						// calculates the file size
						dwFileSize += pSections[i].DataSize;
					}
				}
				// frees the original buffer
				if (VirtualFree(pPackage, 0, MEM_RELEASE))
				{
					// sets the new buffer
					this->pPackage = pUpdatedPackage;
					// sets the new package size
					this->dwSize = dwFileSize;
					// validates the package
					if (Validate())
					{
						// function succeeded
						return TRUE;
					}
				}
				// checks if the file should be compressed
				// compresses the data
				// checks if the file should be encrypted
				// we change the size attribute to the new size
				// writes the data to the buffer
				// calculates the offset of the next file
			}
		}
	}
	return 0;
}

// writes the package to the disk
BOOL Package::Save(LPCSTR lpPackageName)
{
	// opens the requested package
	if (HANDLE hPackage = CreateFileA(lpPackageName, GENERIC_WRITE, FILE_SHARE_ALL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL))
	{
		// stores the number of bytes written
		DWORD dwBytes;
		// writes the package to the disk
		if (WriteFile(hPackage, this->pPackage, this->dwSize, &dwBytes, NULL))
		{
			// function success
			return TRUE;
		}
	}
	// function failed
	return FALSE;
}

// validates the package and returns true if the package is valid
BOOL Package::Validate()
{
	// casts the pointer to a package header
	PPACKAGE_HEADER pHeader = (PPACKAGE_HEADER)pPackage;
	// validates the fourcc code and the package version
	if (pHeader->FourCC == FOURCC && pHeader->Version <= 1)
	{
		// used to calculate the file size
		DWORD dwFileSize = sizeof(PACKAGE_HEADER) + (sizeof(PACKAGE_SECTION) * pHeader->NumberOfSections);
		// gets the package sections array
		PPACKAGE_SECTION pSections = (PPACKAGE_SECTION)pHeader + 1;
		// iterates through the package sections
		for (int i = 0; i < pHeader->NumberOfSections; i++)
		{
			// validates the section attributes
			if (!pSections[i].FileName || dwFileSize != pSections[i].DataOffset || pSections[i].DataSize > 0x6400000 || pSections[i].DataInfo & 0xFFFFFFFC)
			{
				// file is not valid
				return FALSE;
			}
			// calculates the file size
			dwFileSize += pSections[i].DataSize;
		}
		// checks the file size
		if (dwFileSize == dwSize)
		{
			// file is valid
			return TRUE;
		}
	}
	// file is not valid
	return FALSE;
}

// reads the specified package into a buffer
BOOL Package::Read(LPCSTR lpPackage)
{
	// opens the requested package
	this->hPackage = CreateFileA(lpPackage, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_ALL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// validates the handle
	if (this->hPackage != INVALID_HANDLE_VALUE)
	{
		// gets the package size
		this->dwSize = GetFileSize(this->hPackage, NULL);
		// validates the package size
		if (this->dwSize != INVALID_FILE_SIZE)
		{
			// creates a buffer for the package
			this->pPackage = VirtualAlloc(NULL, this->dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			// validates the buffer
			if (this->pPackage)
			{
				// stores the number of bytes read
				DWORD dwBytes;
				// reads the package into the buffer
				if (ReadFile(this->hPackage, this->pPackage, this->dwSize, &dwBytes, NULL) && dwBytes == this->dwSize)
				{
					// validates the package
					if (this->Validate())
					{
						// funtion succeeded
						return TRUE;
					}
				}
			}
		}
	}
	// function failed
	return FALSE;
}

// return the section associated with the file name
PPACKAGE_SECTION Package::GetSection(LPCSTR lpFile)
{
	// casts the pointer to a package header
	PPACKAGE_HEADER pHeader = (PPACKAGE_HEADER)pPackage;
	// gets the package sections array
	PPACKAGE_SECTION pSections = (PPACKAGE_SECTION)pHeader + 1;
	// iterates through the package sections
	for (int i = 0; i < pHeader->NumberOfSections; i++)
	{
		// checks the package name
		if (_stricmp(pSections[i].FileName, lpFile) == 0)
		{
			// returns a pointer
			return &pSections[i];
		}
	}
	// function failed
	return NULL;
}

// retrieves the specified file from the package
PVOID Package::Get(LPCSTR lpFile, PDWORD dwSize)
{
	// gets the section associated with the file
	if (PPACKAGE_SECTION pSection = GetSection(lpFile))
	{
		// gets the file data address
		PVOID pData = (PBYTE)pPackage + pSection->DataOffset;
		// gets the file size
		DWORD dwDataSize = pSection->DataSize;
		// checks if the file is encrypted
		if (pSection->DataInfo & 0b10)
		{
			// gets the unencrypted data size
			DWORD dwDecryptedSize = *(DWORD*)pData;
			// validates the size
			if (dwDecryptedSize - 1 <= 0x63FFFFF)
			{
				// gets the encrypted data
				PVOID pEncrypted = (PBYTE)pData + 4;
				// creates a buffer to store the decrypted file
				pData = VirtualAlloc(NULL, dwDecryptedSize + 0x10, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				// decrypts the file
				if (!DecryptData((PDWORD)pEncrypted, dwDataSize - 4, (PDWORD)pData))
				{
					// frees the buffer
					VirtualFree(pData, 0, MEM_RELEASE);
					// process failed
					return NULL;
				}
				// sets the new data size
				dwDataSize = dwDecryptedSize + 0x10;
			}
			else
			{
				// process failed
				return NULL;
			}
		}
		// checks if the file is compressed
		if (pSection->DataInfo & 0b1)
		{
			// gets the decompressed data size
			DWORD dwDecompressedSize = *(DWORD*)pData;
			// validates the size
			if (dwDecompressedSize - 1 <= 0x63FFFFF)
			{
				// gets the compressed data
				PVOID pCompressed = (PBYTE)pData + 4;
				// creates a buffer to store the decompressed file
				pData = VirtualAlloc(NULL, dwDecompressedSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				// decompresses the file
				if (uncompress((PBYTE)pData, &dwDecompressedSize, (PBYTE)pCompressed, dwDataSize - 4) != Z_OK)
				{
					// frees the buffer
					VirtualFree(pData, 0, MEM_RELEASE);
					// process failed
					return NULL;
				}
				// sets the new data size
				dwDataSize = dwDecompressedSize;
			}
			else
			{
				// process failed
				return NULL;
			}
		}
		// sets the file size
		*dwSize = dwDataSize;
		// returns the pointer to the data
		return pData;
	}
	// function failed
	return NULL;
}

// opens the specified package
Package* Package::Open(LPCSTR lpPackage)
{
	// creates a new package object
	if (Package* pPackage = new Package())
	{
		// reads the requested package
		if (pPackage->Read(lpPackage))
		{
			// function succeeded
			return pPackage;
		}
		// deletes the package instance
		delete pPackage;
	}
	// function failed
	return NULL;
}