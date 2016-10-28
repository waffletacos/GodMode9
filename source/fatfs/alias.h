#pragma once

#include "common.h"
#include "ff.h"

typedef struct {
    u8 iv[16];
    u8 keyy[16];
    u32 keyslot;
} __attribute__((packed)) XFIL;

// wrapper functions for ff.h
// incomplete(!) extension to FatFS to support on-the-fly crypto & path aliases
FRESULT fx_open (FIL* fp, XFIL* xfp, const TCHAR* path, BYTE mode);
FRESULT fx_read (FIL* fp, XFIL* xfp, void* buff, UINT btr, UINT* br);
FRESULT fx_write (FIL* fp, XFIL* xfp, const void* buff, UINT btw, UINT* bw);
FRESULT fa_open (FIL* fp, const TCHAR* path, BYTE mode);
FRESULT fa_opendir (DIR* dp, const TCHAR* path);
FRESULT fa_stat (const TCHAR* path, FILINFO* fno);

// special functions for access of virtual NAND SD drives
bool SetupNandSdDrive(const char* path, const char* sd_path, const char* movable, int num);
bool SetupAliasDrive(const char* path, const char* alias, int num);
bool CheckAliasDrive(const char* path);