/*
Data: 2017-6-17
Autor:  wuych
*/
#ifndef __drv_flash_h
#define __drv_flash_h


#include "gd32f30x.h"



#define FLASH_ZOOM_ALL 0
#define FLASH_ZOOM_BOOT 1
#define FLASH_ZOOM_APP 2
#define FLASH_ZOOM_PARAM 3
#define FLASH_ZOOM_MARK 4


#define FLASH_SIZE 0x40000 // 256k
#define FLASH_BOOT_SIZE 0x8000 //32k
#define FLASH_APP_SIZE 0x10000 //64k
#define FLASH_DATA_SIZE 0x20000 //128k
#define FLASH_PARAM_SIZE 0x800 // 2k
#define FLASH_MARK_SIZE 0x800 // 2k



#define FLASH_BASE_ADDR 0x08000000
#define FLASH_BOOT_ADDR FLASH_BASE_ADDR
#define FLASH_APP_ADDR (FLASH_BOOT_ADDR+FLASH_BOOT_SIZE)
#define FLASH_DATA_ADDR (FLASH_APP_ADDR+FLASH_APP_SIZE)
#define FLASH_PARAM_ADDR (FLASH_DATA_ADDR+FLASH_DATA_SIZE)
#define FLASH_MARK_ADDR (FLASH_PARAM_ADDR+FLASH_MARK_SIZE)



#define STM_SECTOR_SIZE	2048


#define fmc_halfword_read(addr)  (*(vu16*)addr)
//#define FLASH_ProgramHalfWord(addr, data) *(vu16*)addr=data

void FLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);
void FLASH_Write(u8 Zoom, u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);


#endif
