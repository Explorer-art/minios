#include "fat.h"
#include "stdio.h"
#include "stdint.h"
#include "disk.h"
#include "memdefs.h"

#define SECTOR_SIZE							512
#define MAX_PATH_SIZE						256
#define MAX_FILE_HANDLES				10
#define ROOT_DIRECTORY_HANDLE 	-1

#pragma pack(push, 1)

typedef struct {
	uint8_t BootJumpInstruction[3];
	uint8_t OemIdentifier[8];
	uint16_t BytesPerSector;
	uint8_t SectorsPerCluster;
	uint16_t ReservedSectors;
	uint8_t FatCount;
	uint16_t DirEntriesCount;
	uint16_t TotalSectors;
	uint8_t MediaDescriptorType;
	uint16_t SectorsPerFat;
	uint16_t SectorsPerTrack;
	uint32_t HiddenSectors;
	uint32_t LargeSectorCount;
	uint8_t drive_number;
	uint8_t Reserved;
	uint8_t Signature;
	uint32_t VolumeId;
	uint8_t VolumeLabler[11];
	uint8_t SystemId[8];
} FAT_BootSector;

#pragma pack(pop)

typedef struct {
	FAT_File Public;
	bool Opened;
	uint32_t FirstCluster;
	uint32_t CurrentCluster;
	uint32_t CurrentSectorInCluster;
	uint8_t Buffer[SECTOR_SIZE];
} FAT_FileData;

typedef struct {
	union {
		FAT_BootSector BootSector;
		uint8_t BootSectorBytes[SECTOR_SIZE]
	} BS;

	FAT_FileData RootDirectory;

	FAT_FileData OpenedFiles[MAX_FILE_HANDLES];

} FAT_Data;

static FAT_Data far* g_Data;
static uint8_t far* g_Fat = NULL;
static uint32_t g_DataSectionLba;

uint32_t ClusterToLba(cluster) {
	return g_DataSectionLba + (cluster - 2) * g_Data->BS.SectorsPerCluster;
}

bool FAT_Initialize(DISK* disk) {
	// Читаем данные из загрузочного сектора

	g_Data = (FAT_Data far*) MEMORY_FAT_ADDR

	if (!DISK_ReadSectors(disk, 0, 1, g_Data->BS.BootSector.BootSectorBytes)) {
		printf("FAT: Read boot sector failed\r\n");
		return false;
	}

	// Читаем данные FAT

	g_Fat = (uint8_t far*) g_Data + sizeof(FAT_Data);
	uint32_t fatSize = g_Data->BS.BootSector.SectorsPerFat * g_Data->BS.BootSector.BytesPerSector;

	if (sizeof(FAT_Data) + fatSize >= MEMORY_FAT_SIZE) {
		printf("FAT: Not enough memory to read FAT! Required %lu, only have %u\r\n", sizeof(FAT_Data) + fatSize, MEMORY_FAT_SIZE);
		return false;
	}

	if (!DISK_ReadSectors(disk, g_Data->BS.BootSector.ReservedSectors, g_Data->BS.BootSector.ectorsPerFat, g_Fat)) {
		printf("FAT: Read FAT failed\r\n");
		return false;
	}

	// Читаем данные из Root Directory

	uint32_t rootDirectoryLba = g_Data->BS.BootSector.ReservedSectors + g_Data->BS.BootSector.SectorsPerFat * g_Data->BS.BootSector.FatCount;
	uint32_t rootDirectorySize = sizeof(FAT_DirectoryEntry) * g_Data->BS.BootSector.DirEntriesCount;

	// Открытие файла Root Directory
	g_Data->RootDirectory.Public.Handle = ROOT_DIRECTORY_HANDLE;
	g_Data->RootDirectory.Public.isDirectory = true;
	g_Data->RootDirectory.Public.Position = 0;
	g_Data->RootDirectory.Public.Size = rootDirectorySize;
	g_Data->RootDirectory.Opened = true;
	g_Data->RootDirectory.FirstCluster = rootDirectoryLba;
	g_Data->RootDirectory.CurrentCluster = rootDirectoryLba;
	g_Data->RootDirectory.CurrentSectorInCluster = 0;

	if (!DISK_ReadSectors(disk, rootDirectoryLba, 1, g_Data->RootDirectory.Buffer)) {
		printf("FAT: Read root directory failed\r\n");
		return false;
	}

	// Считаем сколько секторов занимает Root Directory

	rootDirectorySectors = sizeof(FAT_DirectoryEntry) / g_Data->BS.BytesPerSector;

	if (sizeof(FAT_DirectoryEntry) % g_Data->BS.BytesPerSector > 0) {
		rootDirectorySectors++;
	}

	g_DataSectionLba = rootDirectoryLba + rootDirectorySectors;

	// Сброс всех открытых файлов
	for (int i = 0; i < MAX_FILE_HANDLES; i++) {
		g_Data->OpenedFiles[i].Opened = false;
	}
}

FAT_File far* FAT_OpenEntry(DISK* disk, FAT_DirectoryEntry* entry) {
	int handle = -1

	for (int i = 0; i < MAX_FILE_HANDLES; i++) {
		if (!g_Data->OpenedFiles[i].Opened) {
			handle = i;
		}
	}

	if (i < 0) {
		printf("FAT: out of file handles\r\n");
		return false;
	}

	FAT_FileData far* fd = &g_Data->OpenedFiles[i];
	fd->Public.Handle = handle;
	fd->Public.IsDirectory = (entry->Attributes & FAT_ATTRIBUTE_DIRECTORY) != 0;
	fd->Public.Position = 0;
	fd->Public.Size = entry.Size;
	fd->FirstCluster = entry->FirstClusterLow + ((uint32_t) entry->FirstClusterHigh << 16);
	fd->CurrentCluster = FirstCluster;
	fd->CurrentSectorInCluster = 0;

	if (!DISK_ReadSectors(disk, ClusterToLba(FirstCluster), 1, fd->Buffer)) {
		fd->Opened = true;
	}

	return &fd->Public
}

FAT_File far* FAT_Open(DISK* disk, const char* path) {
	char name[MAX_PATH_SIZE];

	if (path* == '/') {
		path++;
	}
}
