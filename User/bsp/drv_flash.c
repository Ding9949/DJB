/*
Data: 2017-6-17
Autor:  wuych
*/
#include "drv_flash.h"



u16 STMFLASH_BUF[STM_SECTOR_SIZE>>1];//最多是2K字节

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数
void FLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=fmc_halfword_read(ReadAddr);//读取2个字节.
		ReadAddr+=2;//偏移2个字节.	
	}
}

//不检查的写入
//WriteAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数   
void FLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		fmc_halfword_program(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//地址增加2.
	}  
} 
//从指定地址开始写入指定长度的数据
//Zoom: 指定哪个地址段
//WriteAddr:起始地址(此地址必须为2的倍数!!)
//pBuffer:数据指针
//NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)	 
void FLASH_Write(u8 Zoom, u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址


	//指定空间
	if(Zoom)
	{
		 if(Zoom == FLASH_ZOOM_BOOT)
		 {
			if(WriteAddr<FLASH_BOOT_ADDR||(WriteAddr>=(FLASH_BOOT_ADDR+FLASH_BOOT_SIZE)))return;//非法地址
		}
		else if( Zoom == FLASH_ZOOM_APP)
		{
			if(WriteAddr<FLASH_ZOOM_APP||(WriteAddr>=(FLASH_APP_ADDR+FLASH_APP_SIZE)))return;//非法地址

		}
		else if( Zoom == FLASH_ZOOM_PARAM)
		{
			if(WriteAddr<FLASH_ZOOM_PARAM||(WriteAddr>=(FLASH_PARAM_ADDR+FLASH_PARAM_SIZE)))return;//非法地址

		}
		else if( Zoom == FLASH_ZOOM_MARK)
		{
			if(WriteAddr<FLASH_ZOOM_MARK||(WriteAddr>=(FLASH_MARK_ADDR+FLASH_MARK_SIZE)))return;//非法地址

		}
		else
			return;
	}



	
	fmc_bank0_unlock();						//解锁

	/* clear all pending flags */
	fmc_flag_clear(FMC_FLAG_BANK0_END);
	fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
	fmc_flag_clear(FMC_FLAG_BANK0_PGERR);


	offaddr=WriteAddr-FLASH_BASE_ADDR;		//实际偏移地址.
	secpos=offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//扇区剩余空间大小   
	if(NumToWrite<=secremain)secremain=NumToWrite;//不大于该扇区范围
	while(1) 
	{	
		FLASH_Read(secpos*STM_SECTOR_SIZE+FLASH_BASE_ADDR,STMFLASH_BUF,STM_SECTOR_SIZE/2);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			fmc_page_erase(secpos*STM_SECTOR_SIZE+FLASH_BASE_ADDR);//擦除这个扇区
			for(i=0;i<secremain;i++)//复制
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			FLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+FLASH_BASE_ADDR,STMFLASH_BUF,STM_SECTOR_SIZE/2);//写入整个扇区  
		}else FLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;				//扇区地址增1
			secoff=0;				//偏移位置为0 	 
		   	pBuffer+=secremain;  	//指针偏移
			WriteAddr+=secremain;	//写地址偏移	   
		   	NumToWrite-=secremain;	//字节(16位)数递减
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//下一个扇区还是写不完
			else secremain=NumToWrite;//下一个扇区可以写完了
		}	 
	};	
	fmc_bank0_lock();//上锁
}


