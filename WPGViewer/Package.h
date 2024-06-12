#include <Windows.h>
#include <zlib.h>
#include "Decryptor.h"

// defines the unique fourcc code used to identify the file format
#define FOURCC 0x474B5052
// defines the max length of a package name
#define MAX_PACK_NAME 0x80

#define ACTION_COMPRESS 0b1
#define ACTION_ENCRYPT 0b10

#define FILE_SHARE_ALL (FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE)

// definition of the structure of a package file header
typedef struct _PACKAGE_HEADER
{
	// the package fourcc code
	DWORD FourCC;
	// the package version
	DWORD Version;
	// contains the package root name	
	CHAR PackageRoot[MAX_PACK_NAME];
	// contains the number of sections within the package
	DWORD NumberOfSections;
} PACKAGE_HEADER, *PPACKAGE_HEADER;

// definition of the structure of a package file section
typedef struct _PACKAGE_SECTION
{
	// the name of the file accociated with the section
	CHAR FileName[MAX_PACK_NAME]; // 0x0
								  // the offset of the data block from the base of the file
	DWORD DataOffset; // 0x80
					  // the size of the data block
	DWORD DataSize; // 0x84
					// contains information on whether the data is encrypted or compressed
					// and with bitmask 1 to see if the data is compressed
					// and with bitmast 2 to see if data is encrypted
	DWORD DataInfo; // 0x88
} PACKAGE_SECTION, *PPACKAGE_SECTION;

// definition of the file class
// used to interact with wpg packages
class File
{
private:
public:
	// contains the file name
	LPCSTR lpName;
	// defines the class constructor
	File(LPCSTR lpName, DWORD dwSize, PVOID pData);
};

// definition of the package class
// used to interact with wpg packages
class Package
{
private:
	// defines the class constructor
	// Package();
	// stores a handle to the opened package
	HANDLE hPackage;
	// stores the package in memory
	PVOID pPackage;
	// stores the package size in memory
	DWORD dwSize;
	PPACKAGE_SECTION GetSection(LPCSTR lpFile);
public:
	// a pointer to an array of files contained within the package
	// File* pFiles;
	// the number of files within the package
	// DWORD dwCount;
	// opens the specified package
	static Package* Open(LPCSTR lpPackage);
	// gets the specified file from the opened package
	// File* Get(LPCSTR lpName);
	// validates the package
	BOOL Validate();
	// updates the package
	BOOL Update(LPCSTR lpName, PVOID pData, DWORD dwDataSize, DWORD dwAction);
	BOOL Read(LPCSTR lpPackage);
	PVOID Get(LPCSTR lpFile, PDWORD dwSize);
	BOOL Save(LPCSTR lpPackageName);
};