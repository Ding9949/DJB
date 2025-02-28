#include "sys_include.h"





iapfun jump2app;  
u16 iapbuf[IAP_SECTOR_SIZE>>1] ={0,};   
IapMarkInfo_t IapMarkInfo;
IapSectorBuf_t RxSector;
IapSectorBuf_t SaveSector;
Iap_t IapCtl;

RS485_T RS485;

__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}


u16 sum_check(u8 * dpin,u16 len)
{
	u16 i=0,sum=0;
	for(i=0;i<len;i++)
	{
		sum += *(dpin+i);
	}
	return sum;

}


void iap_init(void)
{
	memset(&IapCtl, 0, sizeof(Iap_t));
	memset(&RS485, 0, sizeof(RS485_T));

	RS485.RxdLen = RS485_TX_MAX;
}

void iap_get_mark(void)
{
	FLASH_Read(FLASH_MARK_ADDR, (u16*)&IapMarkInfo, (sizeof( IapMarkInfo_t)>>1));
}


void iap_save_mark(void)
{
	FLASH_Write(FLASH_ZOOM_MARK, FLASH_MARK_ADDR, (u16*)&IapMarkInfo, sizeof( IapMarkInfo_t)>>1);
}

//sector:Ӧ�ó���Ķκţ�����ʼ��ַ��ʼ��ÿ��1024�ֽ�
//appbuf:ָ��Ӧ�ó���ĳһ�ε�����
//appsize:��ǰ�������ݴ�С
void iap_write_sector(u8 sector,  u8 *appbuf,u32 appsize)
{
	u32 fwaddr=FLASH_BOOT_ADDR+sector*IAP_SECTOR_SIZE;//��ǰд��ĵ�ַ
	FLASH_Write(FLASH_ZOOM_BOOT, fwaddr,(u16*)appbuf,(appsize>>1));	
}



//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(vu32*)appxaddr);					//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		jump2app();									//��ת��APP.
	}
}		 


void iap_trans_app(u8 sector,  u8 idx, u8* data)
{
	u16 ofs = 0;
	if(idx >=(IAP_SECTOR_SIZE>>3))
		return;

	
	if(RxSector.sector == 0xff)
	{
		RxSector.sector = sector;
		memset(RxSector.idxflag, 0, (IAP_SECTOR_SIZE>>3));		
		RxSector.len = 0;
		RxSector.errflag = 0;
	}
	else if(RxSector.sector !=sector)
	{
		RxSector.errflag = 1;
	}


	ofs = idx*8;

	RxSector.idxflag[idx] = 1;
	RxSector.data[ofs] = data[0];
	RxSector.data[ofs+1] = data[1];
	RxSector.data[ofs+2] = data[2];
	RxSector.data[ofs+3] = data[3];
	RxSector.data[ofs+4] = data[4];
	RxSector.data[ofs+5] = data[5];
	RxSector.data[ofs+6] = data[6];
	RxSector.data[ofs+7] = data[7];

	RxSector.len+=8;


	

	

	
	
}


void iap_parse_can_msg(CanMsg_t* pMsg)
{
	u8 cmd = 0;
	u8 ads = 0;
	u8 sector = 0;
	u8 idx = 0;

	
	cmd = (pMsg->ExtId>>8)&0xFF;
	ads = pMsg->ExtId&0xFF;

	if(ads != gSysPar.SysAds && ads !=0)
		return ;

	switch (cmd)
	{
	case CAN_CMD_IAP_UPDATE:
		IapCtl.CmdUpdate = 1;
		break;
	case CAN_CMD_IAP_READY:
		IapCtl.CmdReady = 1;
		break;
	case CAN_CMD_IAP_TRANS:
		sector = (pMsg->ExtId>>23)&0x3F;
		idx = (pMsg->ExtId>>16)&0x7F;
		iap_trans_app(sector, idx, pMsg->Data);
		break;
	case CAN_CMD_IAP_FINISH_SECTOR:
		IapCtl.CmdFinishSector = 1;
	
 
		break;	
	case CAN_CMD_IAP_FINISH_ALL:
		IapCtl.UpErr = pMsg->Data[0];
		IapCtl.CmdFinishAll = 1;
		break;
	default:break;

	}


}




void iap_process(void)
{
	MonVar.MonSts = MON_AUTO_MID;
	CanMsg_t TxMessage={0,};
	if(IapCtl.Sts == STS_INIT)
	{
		#if 0
		iap_get_mark();
		if(IapMarkInfo.IapMarkWord != 1 && IapMarkInfo.IapMarkWord != 2 )
		{
			
	
				
			//save mark info
			IapMarkInfo.BootVer =  CODE_VER;
			iap_save_mark();
			IapCtl.Sts = STS_START_APP;
		}
		else 
		{
			IapCtl.Sts = STS_UPDATE;
			IapCtl.TimeOutCnt = SYS_ISR_PSC*1000*10;   //  10 s
			IapCtl.CmdReady = 0;
		}
		#endif

		
		IapCtl.Sts = STS_UPDATE;
		IapCtl.TimeOutCnt = SYS_ISR_PSC*1000*10;   //  10 s
		IapCtl.CmdReady = 0;
		IapCtl.UpErr = 0;

	}

	else if(IapCtl.Sts == STS_UPDATE)
	{
		if(IapCtl.CmdUpdate ==  1)
		{
			//ack cmd_ready//ack cmd_finish_sector
			//TxMessage.IDE=CAN_Id_Extended;			
			TxMessage.ExtId=(CAN_CMD_IAP_UPDATE<<8)|gSysPar.SysAds;		
			TxMessage.Data[0]=1;				
			TxMessage.DLC=1;							
			can_send_msg(&TxMessage);
			
			IapCtl.CmdUpdate = 0;
			IapCtl.UpErr = 0;
		}
		else if(IapCtl.CmdReady == 1)
		{
			//ack cmd_ready//ack cmd_finish_sector
			//TxMessage.IDE=CAN_Id_Extended;			
			TxMessage.ExtId=(CAN_CMD_IAP_READY<<8)|gSysPar.SysAds;		
			TxMessage.Data[0]=1;				
			TxMessage.DLC=1;							
			can_send_msg(&TxMessage);


			IapCtl.CmdReady = 0;
			IapCtl.UpErr = 0;
		}
		if(IapCtl.CmdFinishSector ==  1)
		{
			u8 i = 0;
			for(i=0;i<(IAP_SECTOR_SIZE>>3);i++)
			{
				if(RxSector.idxflag[i]!=1)
				{
					RxSector.errflag = 1;
					break;
				}
			}

			//save one sector 
			if(RxSector.errflag == 0)
			{
				memcpy(&SaveSector, &RxSector, sizeof(IapSectorBuf_t));
				iap_write_sector(SaveSector.sector, SaveSector.data, SaveSector.len);
			}
			
			
			
			//ack cmd_finish_sector
			//TxMessage.IDE=CAN_Id_Extended;			
			TxMessage.ExtId=(CAN_CMD_IAP_FINISH_SECTOR<<8)|gSysPar.SysAds;		
			TxMessage.Data[0]=1;
			TxMessage.Data[1]=RxSector.errflag;				
			TxMessage.DLC=2;							
			can_send_msg(&TxMessage); 

			RxSector.errflag = 0;
			RxSector.sector = 0xff;

			IapCtl.CmdFinishSector = 0;
		}
		else if(IapCtl.CmdFinishAll ==  1)
		{
			//ack cmd_finish
			//TxMessage.IDE=CAN_Id_Extended;			
			TxMessage.ExtId=(CAN_CMD_IAP_FINISH_ALL<<8)|gSysPar.SysAds;		

			
			TxMessage.Data[0]=1;				
			TxMessage.DLC=1;							
			can_send_msg(&TxMessage);

			IapCtl.Sts = STS_FINISH;
			IapCtl.CmdFinishAll = 0;
			
		}

	}
	else if(IapCtl.Sts == STS_FINISH)
	{
		#if 0
		IapMarkInfo.IapMarkWord = 2;

		//save mark info
		iap_save_mark();
		#endif

		if(IapCtl.UpErr == 0)
		{
			IapCtl.Sts = STS_START_APP;
		}
		else
		{
			IapCtl.Sts = STS_INIT;
		}
		


	}
	else if(IapCtl.Sts == STS_START_APP)
	{

		//TIM_DeInit(TIM1);
		//CAN_DeInit(CAN1);
	
		//iap_load_app(FLASH_APP_ADDR);
		delay_ms(100);
		NVIC_SystemReset();
	}


	




}



void iap_485_rx(void)
{
	u8 temp = USARTB_RXD(); 
	if(RS485.RxdFlag) 
	{
		// ��һ֡����δ����
		return;
	}


	//--------------------------------------------------------------//
	//�����ж�	
	if(RS485.RxdIndex>= RS485.RxdLen && RS485.RxdLen){
		RS485.RxdIndex= 0;
	}
	if(RS485.RxdTicker == 0 && RS485.RxdIndex)
	{
		RS485.RxdIndex= 0;
	}
	RS485.RxdTicker = 100;//5ms
	//--------------------------------------------------------------//	
	
	//--------------------------------------------------------------//
	//���ݻ���	
	RS485.RecBuf[RS485.RxdIndex] = temp;
	//--------------------------------------------------------------//

	//--------------------------------------------------------------//
	//ͷ���ж�
	if(RS485.RecBuf[0] != RS485_RX_HEAD1)
	{
		RS485.RxdIndex= 0;
		return;
	}
	else if(RS485.RxdIndex ==1)
	{

		if(RS485.RecBuf[1] == 0)//Ⱥ������
		{
			RS485.RxdLen =  RS485_TX_MAX;
		}
		else
		{
			RS485.RxdLen =  RS485_RX_MAX;
		}
	}
	else if(RS485.RxdIndex== RS485.RxdLen-1&& RS485.RxdIndex >3)
	{

		RS485.RxdFlag = TRUE;
		RS485.RxdIndex = 0;
	}
	
	RS485.RxdIndex++;
	
}


void iap_485_tx(u16 len)
{
	if(RS485.TxdSts == 0)//��������
	{
		SCI_B_DE_CTL(USART_BUS_TXD);
		RS485.TxdSts = 1;
	}
	else if(RS485.TxdSts==1)//�ȴ��������
	{
		USARTB_TC_CLR();           // �巢�����״̬
		USARTB_TXD(RS485.TxdBuf[0]);
		 
		RS485.TxdCnt = 0;
		RS485.TxdLen = len;	
		RS485.TxdSts = 2;
	}
	else
	{
	
	}



}





void iap_485_process(void)
{
	u16 temp = 0;
	u8 sum_checkk = 0;
	//u16 crc_check = 0;
	//u16 crc_checkk = 0;
	//u16 len = 0;
	//u16 sector = 0;
	//u32 addr = 0;
	


	
	if(RS485.TxdFlag)
	{	
		
		if(RS485.TxdDly)
		{
			SCI_B_DE_CTL(USART_BUS_TXD);			
		}
		else
		{
			iap_485_tx(RS485.TxdLen);
		}
		
		return;

	}
		
	
	if(RS485.RxdFlag == FALSE){
		// �ȴ��������
		return;
	}



	// ��ַ=0:  Ⱥ������
	if(RS485.RecBuf[1] == 0)
	{
		//�ж�У�����Ƿ���ȷ У��( 1�������ڶ������ĺ�)
		temp = sum_check(&RS485.RecBuf[1],RS485.RxdLen-2);
		sum_checkk = temp&0xff;
		if(RS485.RecBuf[RS485.RxdLen-1] != sum_checkk)
		{
			
			goto LoopErrEnd;
		}


		// ��ַ=0  ������= 0x24  : ����֡
		if(RS485.RecBuf[2] == RS485_CMD_IAP_UPDATE)
		{

			iap_get_mark();	
			IapMarkInfo.AppVer = CODE_VER;
			IapMarkInfo.IapMarkWord = 3;	
			iap_save_mark();
			delay_ms(100);
			NVIC_SystemReset();


		}
		// ��ַ=0  ������= 0x25  : �˳�֡
		else if(RS485.RecBuf[2] == RS485_CMD_IAP_EXIT)
		{
		}
		
	}
	#if 0
	// ��������
	else if(RS485.RecBuf[1] == IapMarkInfo.ID && RS485.RecBuf[2] == RS485_CMD_IAP_UPDATE)
	{
		//�ж�У�����Ƿ���ȷ У��
		crc_checkk = GetCRC16(RS485.RecBuf,RS485.RxdLen-2);
		crc_check = (RS485.RecBuf[RS485.RxdLen-2]<<8)+RS485.RecBuf[RS485.RxdLen-1];
		if(crc_check != crc_checkk)
		{
			goto LoopErrEnd;
		}

		len = (RS485.RecBuf[3]<<8)+RS485.RecBuf[4];
		if(len >IAP_SECTOR_SIZE)len = IAP_SECTOR_SIZE;
	
		sector = RS485.RecBuf[5] - 1;
		addr = sector*IAP_SECTOR_SIZE;
	
		if(addr < FLASH_APP_SIZE)
		{
			if(len == 0)
				iap_write_sector(sector, &RS485.RecBuf[6], IAP_SECTOR_SIZE);
			else
				iap_write_sector(sector, &RS485.RecBuf[6], len);
		}

		//�����ͽ���
		if(len)
		{
			delay_ms(10);
			IapMarkInfo.IapMarkWord = 4;
			//save mark info
			iap_save_mark();
			delay_ms(10);
			iap_start_app();
		
		}

	}
	#endif


	
	
	if(RS485.TxdFlag)
		return ;

LoopErrEnd:	
	memset(RS485.RecBuf,0,RS485_RX_MAX);
	RS485.RxdFlag = 0;
	RS485.RxdIndex = 0;
}




