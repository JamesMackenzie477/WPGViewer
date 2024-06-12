#include "WPGViewer.h"

PVOID ReadBinaryFile(LPCSTR lpFile, PDWORD dwOut)
{
	// opens the requested file
	HANDLE hFile = CreateFileA(lpFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// validates the handle
	if (hFile != INVALID_HANDLE_VALUE)
	{
		// gets the file size
		DWORD dwSize = GetFileSize(hFile, NULL);
		// validates the file size
		if (dwSize != INVALID_FILE_SIZE)
		{
			// creates a buffer for the file
			PVOID pFile = VirtualAlloc(NULL, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			// validates the buffer
			if (pFile)
			{
				// stores the number of bytes read
				DWORD dwBytes;
				// reads the file into the buffer
				if (ReadFile(hFile, pFile, dwSize, &dwBytes, NULL) && dwBytes == dwSize)
				{
					// closes the file handle
					CloseHandle(hFile);
					// sets the output size
					*dwOut = dwSize;
					// funtion succeeded
					return pFile;
				}
				// frees the buffer
				VirtualFree(pFile, 0, MEM_RELEASE);
			}
		}
		// closes the file handle
		CloseHandle(hFile);
	}
	// function failed
	return FALSE;
}

// the main entry of the program
int main(int argc, char *argv[])
{
	// validates the argument count
	if (argc == 5)
	{
		// opens the requested package
		if (Package* pPackage = Package::Open(argv[1]))
		{
			// stores the file size
			DWORD dwFileSize;
			// opens the new file
			if (PVOID pFile = ReadBinaryFile(argv[3], &dwFileSize))
			{
				// writes the file to the package
				if (pPackage->Update(argv[2], pFile, dwFileSize, ACTION_COMPRESS))
				{
					// saves the file to the disk
					if (pPackage->Save(argv[4]))
					{
						std::cout << "cool" << std::endl;
					}
				}
			}
		}
	}
	// waits to exit
	std::cin.get();
	// exits program
	return 0;
}