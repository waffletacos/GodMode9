#pragma once

#include "common.h"

#define FIRM_MAGIC  'F', 'I', 'R', 'M'

#define SECTOR_NAME "sector0x96.bin"
#define SECRET_NAME "secret_sector.bin"

#define FIRM_MAX_SIZE  0x400000 // 4MB, due to FIRM partition size
#define ARM9BIN_OFFSET 0x800
#define ARM11V2_OFFSET 0x2B000

// see: https://www.3dbrew.org/wiki/FIRM#Firmware_Section_Headers
typedef struct {
    u32 offset;
    u32 address;
    u32 size;
    u32 type;
    u8  hash[0x20];
} __attribute__((packed)) FirmSectionHeader;

// see: https://www.3dbrew.org/wiki/FIRM#FIRM_Header
typedef struct {
    u8  magic[4];
    u8  dec_magic[4];
    u32 entry_arm11;
    u32 entry_arm9;
    u8  reserved1[0x30];
    FirmSectionHeader sections[4];
    u8  signature[0x100];
} __attribute__((packed, aligned(16))) FirmHeader;

// see: https://www.3dbrew.org/wiki/FIRM#New_3DS_FIRM
typedef struct {
    u8  keyX0x15[0x10]; // this is encrypted
    u8  keyY0x150x16[0x10];
    u8  ctr[0x10];
    char size_ascii[0x8];
    u8  reserved[0x8];
    u8  control[0x10];
    u8  k9l[0x10];
    u8  keyX0x16[0x10]; // this is encrypted
    u8  padding[0x1A0];
} __attribute__((packed, aligned(16))) FirmA9LHeader;

u32 ValidateFirmHeader(FirmHeader* header, u32 data_size);
u32 ValidateFirmA9LHeader(FirmA9LHeader* header);

FirmSectionHeader* FindFirmArm9Section(FirmHeader* firm);
u32 GetArm9BinarySize(FirmA9LHeader* a9l);

u32 SetupArm9BinaryCrypto(FirmA9LHeader* header);
u32 DecryptA9LHeader(FirmA9LHeader* header);
u32 DecryptFirm(u8* data, u32 offset, u32 size, FirmHeader* firm, FirmA9LHeader* a9l);
u32 DecryptArm9Binary(u8* data, u32 offset, u32 size, FirmA9LHeader* a9l);
u32 DecryptFirmSequential(u8* data, u32 offset, u32 size);
