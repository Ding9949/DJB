/*
Data: 2017-6-17
Autor:  wuych
*/
#include "drv_flash.h"



u16 STMFLASH_BUF[STM_SECTOR_SIZE>>1];//�����2K�ֽ�

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��
void FLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=fmc_halfword_read(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}

//������д��
//WriteAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��   
void FLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		fmc_halfword_program(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//��ַ����2.
	}  
} 
//��ָ����ַ��ʼд��ָ�����ȵ�����
//Zoom: ָ���ĸ���ַ��
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
//pBuffer:����ָ��
//NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)	 
void FLASH_Write(u8 Zoom, u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //������ַ
	u16 secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	u16 secremain; //������ʣ���ַ(16λ�ּ���)	   
 	u16 i;    
	u32 offaddr;   //ȥ��0X08000000��ĵ�ַ


	//ָ���ռ�
	if(Zoom)
	{
		 if(Zoom == FLASH_ZOOM_BOOT)
		 {
			if(WriteAddr<FLASH_BOOT_ADDR||(WriteAddr>=(FLASH_BOOT_ADDR+FLASH_BOOT_SIZE)))return;//�Ƿ���ַ
		}
		else if( Zoom == FLASH_ZOOM_APP)
		{
			if(WriteAddr<FLASH_ZOOM_APP||(WriteAddr>=(FLASH_APP_ADDR+FLASH_APP_SIZE)))return;//�Ƿ���ַ

		}
		else if( Zoom == FLASH_ZOOM_PARAM)
		{
			if(WriteAddr<FLASH_ZOOM_PARAM||(WriteAddr>=(FLASH_PARAM_ADDR+FLASH_PARAM_SIZE)))return;//�Ƿ���ַ

		}
		else if( Zoom == FLASH_ZOOM_MARK)
		{
			if(WriteAddr<FLASH_ZOOM_MARK||(WriteAddr>=(FLASH_MARK_ADDR+FLASH_MARK_SIZE)))return;//�Ƿ���ַ

		}
		else
			return;
	}



	
	fmc_bank0_unlock();						//����

	/* clear all pending flags */
	fmc_flag_clear(FMC_FLAG_BANK0_END);
	fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
	fmc_flag_clear(FMC_FLAG_BANK0_PGERR);


	offaddr=WriteAddr-FLASH_BASE_ADDR;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
	while(1) 
	{	
		FLASH_Read(secpos*STM_SECTOR_SIZE+FLASH_BASE_ADDR,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			fmc_page_erase(secpos*STM_SECTOR_SIZE+FLASH_BASE_ADDR);//�����������
			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			FLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+FLASH_BASE_ADDR,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}else FLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		   	pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		   	NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
		}	 
	};	
	fmc_bank0_lock();//����
}


