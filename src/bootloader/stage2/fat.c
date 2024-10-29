#include "fat.h"
#include "stdio.h"
#include "stdint.h"
#include "disk.h"

#define SECTOR_SIZE 512

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

	// extended boot sector

	uint8_t drive_number;
	uint8_t Reserved;
	uint8_t Signature;
	uint32_t VolumeId;
	uint8_t VolumeLabler[11];
	uint8_t SystemId[8];
} FAT_BootSector;

#pragma pack(pop)

typedef struct {
	union {
		FAT_BootSector BootSector;
		uint8_t BootSectorBytes[SECTOR_SIZE]
	} BS;
} FAT_Data;

static FAT_Data far* g_Data;

uint8_t* g_Fat = NULL;
DirectoryEntry* g_RootDirectory = NULL;
uint32_t g_RootDirectoryEnd;

bool FAT_ReadBootSector(DISK* disk) {
	return DISK_ReadSectors(disk, 0, 1, &g_Data->BS.BootSectorBytes);
}

bool FAT_Initialize(DISK* disk) {
	if (!FAT_ReadBootSector(disk)) {
		printf("FAT: Read boot sector failed\r\n");
		return false;
	}
}