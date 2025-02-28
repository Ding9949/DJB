/*
 *
 *  Created on: 2017年8月16日
 *      Author: Wuych
 */


#include "sys_include.h"

ExCom_t gExCom = {0, };



const u8 auchCRCHi[] = {
 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40 
}; 

const u8 auchCRCLo[] = {
 0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
 0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
 0x43, 0x83, 0x41, 0x81, 0x80, 0x40 
};

u16 check_crc16(u8 *puchMsg, u16 usDataLen) 
{   
/* CRC低位字节值表*/ 
  
	u8 uchCRCHi = 0xFF ; /* 高CRC字节初始化 */ 
	u8 uchCRCLo = 0xFF ; /* 低CRC 字节初始化 */ 
	u16 uIndex ; /* CRC循环中的索引 */ 
	while (usDataLen--) /* 传输消息缓冲区 */ 
	{ 
		uIndex = uchCRCHi ^ *puchMsg++ ; /* 计算CRC */ 
		uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ; 
		uchCRCLo = auchCRCLo[uIndex] ; 
	} 
	return (uchCRCHi << 8 | uchCRCLo) ; 
}

//配置ID
static void _parse_data_fx(u8 idx)
{
	u16 temp = 0;
	u8 i = 0;

	//读取UID 和ID
	if(idx == 0)
	{
		if(gExCom.RecBuf[3] == 0)//每200ms 轮询一次
		{
			if(gExCom.UID_ReadFlag == 0)//触发一次
			{
				gExCom.UID_ReadDlyCnt = 2500; // 2.5s  等待can数据
				gExCom.UID_ReadFlag = 1;
				for(i=0;i<MAX_NODE_NUM;i++)//缓存清零
				{
					gCanBusCtl1.UID[i] = 0;
					gCanBusCtl1.ID[i] = 0;
					gCanBusCtl1.UID_Idx = 0;
					gCanBusCtl1.UID_Sts = 0;
				}

				//发送数据
				gCanBusCtl1.TxMsg.ExtId = 0;
				gCanBusCtl1.TxMsg.Data[0] = 0;
				gCanBusCtl1.TxMsg.Data[1] = 0;
				gCanBusCtl1.TxMsg.Data[2] = 0;
				gCanBusCtl1.TxMsg.Data[3] = 0;
				gCanBusCtl1.TxMsg.Data[4] = 1;
				gCanBusCtl1.TxMsg.Data[5] = 0;
				gCanBusCtl1.TxMsg.DLC  = 6;
				can1_buffer_add_msg(&gCanBusCtl1.TxMsg);
			}
		}
		//读取完毕，回传数据
		//else
		{	
			//Ack
			gExCom.TxdBuf[0] = 0x5C;
			gExCom.TxdBuf[1] = 0xf0;
			gExCom.TxdBuf[2] = gExCom.ADS;
			gExCom.TxdBuf[3] = 0;
			gExCom.TxdBuf[4] = gCanBusCtl1.UID[0]>>24;// UID1
			gExCom.TxdBuf[5] = gCanBusCtl1.UID[0]>>16;
			gExCom.TxdBuf[6] = gCanBusCtl1.UID[0]>>8;
			gExCom.TxdBuf[7] = gCanBusCtl1.UID[0]&0xff;
			gExCom.TxdBuf[8] =  gCanBusCtl1.ID[0];
			gExCom.TxdBuf[9] = gCanBusCtl1.UID[1]>>24;// UID2
			gExCom.TxdBuf[10] = gCanBusCtl1.UID[1]>>16;
			gExCom.TxdBuf[11] = gCanBusCtl1.UID[1]>>8;
			gExCom.TxdBuf[12] = gCanBusCtl1.UID[1]&0xff;
			gExCom.TxdBuf[13] =  gCanBusCtl1.ID[1];
			gExCom.TxdBuf[14] = gCanBusCtl1.UID[2]>>24;// UID3
			gExCom.TxdBuf[15] = gCanBusCtl1.UID[2]>>16;
			gExCom.TxdBuf[16] = gCanBusCtl1.UID[2]>>8;
			gExCom.TxdBuf[17] = gCanBusCtl1.UID[2]&0xff;
			gExCom.TxdBuf[18] =  gCanBusCtl1.ID[2];
			gExCom.TxdBuf[19] = gCanBusCtl1.UID[3]>>24;// UID4
			gExCom.TxdBuf[20] = gCanBusCtl1.UID[3]>>16;
			gExCom.TxdBuf[21] = gCanBusCtl1.UID[3]>>8;
			gExCom.TxdBuf[22] = gCanBusCtl1.UID[3]&0xff;
			gExCom.TxdBuf[23] =  gCanBusCtl1.ID[3];
			gExCom.TxdBuf[24] = gCanBusCtl1.UID[4]>>24;// UID5
			gExCom.TxdBuf[25] = gCanBusCtl1.UID[4]>>16;
			gExCom.TxdBuf[26] = gCanBusCtl1.UID[4]>>8;
			gExCom.TxdBuf[27] = gCanBusCtl1.UID[4]&0xff;
			gExCom.TxdBuf[28] =  gCanBusCtl1.ID[4];
			gExCom.TxdBuf[29] = gCanBusCtl1.UID[5]>>24;// UID6
			gExCom.TxdBuf[30] = gCanBusCtl1.UID[5]>>16;
			gExCom.TxdBuf[31] = gCanBusCtl1.UID[5]>>8;
			gExCom.TxdBuf[32] = gCanBusCtl1.UID[5]&0xff;
			gExCom.TxdBuf[33] =  gCanBusCtl1.ID[5];
			gExCom.TxdBuf[34] = gCanBusCtl1.UID[6]>>24;// UID7
			gExCom.TxdBuf[35] = gCanBusCtl1.UID[6]>>16;
			gExCom.TxdBuf[36] = gCanBusCtl1.UID[6]>>8;
			gExCom.TxdBuf[37] = gCanBusCtl1.UID[6]&0xff;
			gExCom.TxdBuf[38] =  gCanBusCtl1.ID[6];
			gExCom.TxdBuf[39] = gCanBusCtl1.UID[7]>>24;// UID8
			gExCom.TxdBuf[40] = gCanBusCtl1.UID[7]>>16;
			gExCom.TxdBuf[41] = gCanBusCtl1.UID[7]>>8;
			gExCom.TxdBuf[42] = gCanBusCtl1.UID[7]&0xff;
			gExCom.TxdBuf[43] =  gCanBusCtl1.ID[7];
			gExCom.TxdBuf[44] = gCanBusCtl1.UID[8]>>24;// UID9
			gExCom.TxdBuf[45] = gCanBusCtl1.UID[8]>>16;
			gExCom.TxdBuf[46] = gCanBusCtl1.UID[8]>>8;
			gExCom.TxdBuf[47] = gCanBusCtl1.UID[8]&0xff;
			gExCom.TxdBuf[48] =  gCanBusCtl1.ID[8];
			gExCom.TxdBuf[49] = gCanBusCtl1.UID[9]>>24;// UID10
			gExCom.TxdBuf[50] = gCanBusCtl1.UID[9]>>16;
			gExCom.TxdBuf[51] = gCanBusCtl1.UID[9]>>8;
			gExCom.TxdBuf[52] = gCanBusCtl1.UID[9]&0xff;
			gExCom.TxdBuf[53] =  gCanBusCtl1.ID[9];
			gExCom.TxdBuf[54] = gCanBusCtl1.UID[10]>>24;// UID11
			gExCom.TxdBuf[55] = gCanBusCtl1.UID[10]>>16;
			gExCom.TxdBuf[56] = gCanBusCtl1.UID[10]>>8;
			gExCom.TxdBuf[57] = gCanBusCtl1.UID[10]&0xff;
			gExCom.TxdBuf[58] =  gCanBusCtl1.ID[10];
			gExCom.TxdBuf[59] = gCanBusCtl1.UID[11]>>24;// UID12
			gExCom.TxdBuf[60] = gCanBusCtl1.UID[11]>>16;
			gExCom.TxdBuf[61] = gCanBusCtl1.UID[11]>>8;
			gExCom.TxdBuf[62] = gCanBusCtl1.UID[11]&0xff;
			gExCom.TxdBuf[63] =  gCanBusCtl1.ID[11];

			gExCom.TxdBuf[64] = 0;
			gExCom.TxdBuf[65] = 0;
			gExCom.TxdBuf[66] = 0;
			gExCom.TxdBuf[67] = 0;
			gExCom.TxdBuf[68] = 0;
			gExCom.TxdBuf[69] = 0;
			gExCom.TxdBuf[70] = 0;
			gExCom.TxdBuf[71] = 0;
			gExCom.TxdBuf[72] = 0;
			gExCom.TxdBuf[73] = 0;
			gExCom.TxdBuf[74] = 0;
			gExCom.TxdBuf[75] = 0;
			gExCom.TxdBuf[76] = 0;
			gExCom.TxdBuf[77] = 0;
			gExCom.TxdBuf[78] = 0;
			gExCom.TxdBuf[79] = 0;
			gExCom.TxdBuf[80] = 0;

			gExCom.TxdBuf[81] = gExCom.UID_ReadFlag;
			
			temp = check_crc16(gExCom.TxdBuf, 82);
			gExCom.TxdBuf[82] = temp>>8;
			gExCom.TxdBuf[83] = temp&0xff;

			gExCom.TxdFlag = 1;
			gExCom.TxdLen = 84;
			gExCom.TxdDly = 5;

		}
	}
	
	//握手一次
	if(idx == 1)
	{
		gExCom.UID = (gExCom.RecBuf[3]<<24) + (gExCom.RecBuf[4]<<16) + (gExCom.RecBuf[5]<<8) + gExCom.RecBuf[6];

		//发送数据
		gCanBusCtl1.TxMsg.ExtId = 0;
		gCanBusCtl1.TxMsg.Data[0] = gExCom.RecBuf[6];
		gCanBusCtl1.TxMsg.Data[1] = gExCom.RecBuf[5];
		gCanBusCtl1.TxMsg.Data[2] = gExCom.RecBuf[4];
		gCanBusCtl1.TxMsg.Data[3] = gExCom.RecBuf[3];
		gCanBusCtl1.TxMsg.Data[4] = 2;
		gCanBusCtl1.TxMsg.Data[5] = 0;
		gCanBusCtl1.TxMsg.DLC  = 6;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);


		//Ack
		gExCom.TxdBuf[0] = 0x5C;
		gExCom.TxdBuf[1] = 0xf1;
		gExCom.TxdBuf[2] = gExCom.ADS;
		gExCom.TxdBuf[3] = gExCom.RecBuf[3];// UID1
		gExCom.TxdBuf[4] = gExCom.RecBuf[4];
		gExCom.TxdBuf[5] = gExCom.RecBuf[5];
		gExCom.TxdBuf[6] = gExCom.RecBuf[6];
		gExCom.TxdBuf[7] = 0;
		gExCom.TxdBuf[8] = 0;
		gExCom.TxdBuf[9] = 0;
		gExCom.TxdBuf[10] = 0;
		gExCom.TxdBuf[11] = 0;
		gExCom.TxdBuf[12] = 0;
		gExCom.TxdBuf[13] = 0;
		gExCom.TxdBuf[14] = 0;
		gExCom.TxdBuf[15] = 0;
		gExCom.TxdBuf[16] = 0;
		gExCom.TxdBuf[17] = 0;
		gExCom.TxdBuf[18] = 0;

		temp = check_crc16(gExCom.TxdBuf, 19);
		gExCom.TxdBuf[19] = temp>>8;
		gExCom.TxdBuf[20] = temp&0xff;

		gExCom.TxdFlag = 1;
		gExCom.TxdLen = 21;
		gExCom.TxdDly = 5;
	}

	//设置新ID
	if(idx == 2)
	{
		gExCom.UID = (gExCom.RecBuf[3]<<24) + (gExCom.RecBuf[4]<<16) + (gExCom.RecBuf[5]<<8) + gExCom.RecBuf[6];
		gExCom.ID = gExCom.RecBuf[7];
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = 0;
		gCanBusCtl1.TxMsg.Data[0] = gExCom.RecBuf[6];
		gCanBusCtl1.TxMsg.Data[1] = gExCom.RecBuf[5];
		gCanBusCtl1.TxMsg.Data[2] = gExCom.RecBuf[4];
		gCanBusCtl1.TxMsg.Data[3] = gExCom.RecBuf[3];
		gCanBusCtl1.TxMsg.Data[4] = 3;
		gCanBusCtl1.TxMsg.Data[5] = gExCom.ID;
		gCanBusCtl1.TxMsg.DLC  = 6;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);


		//Ack
		gExCom.TxdBuf[0] = 0x5C;
		gExCom.TxdBuf[1] = 0xf2;
		gExCom.TxdBuf[2] = gExCom.ADS;
		gExCom.TxdBuf[3] = gExCom.RecBuf[3];// UID1
		gExCom.TxdBuf[4] = gExCom.RecBuf[4];
		gExCom.TxdBuf[5] = gExCom.RecBuf[5];
		gExCom.TxdBuf[6] = gExCom.RecBuf[6];
		gExCom.TxdBuf[7] = gExCom.ID;
		gExCom.TxdBuf[8] = 0;
		gExCom.TxdBuf[9] = 0;
		gExCom.TxdBuf[10] = 0;
		gExCom.TxdBuf[11] = 0;
		gExCom.TxdBuf[12] = 0;
		gExCom.TxdBuf[13] = 0;
		gExCom.TxdBuf[14] = 0;
		gExCom.TxdBuf[15] = 0;
		gExCom.TxdBuf[16] = 0;
		gExCom.TxdBuf[17] = 0;
		gExCom.TxdBuf[18] = 0;

		temp = check_crc16(gExCom.TxdBuf, 19);
		gExCom.TxdBuf[19] = temp>>8;
		gExCom.TxdBuf[20] = temp&0xff;

		gExCom.TxdFlag = 1;
		gExCom.TxdLen = 21;
		gExCom.TxdDly = 5;
	}

	//退出
	if(idx == 2)
	{
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = 0;
		gCanBusCtl1.TxMsg.Data[0] = 0xFF;
		gCanBusCtl1.TxMsg.Data[1] = 0xFF;
		gCanBusCtl1.TxMsg.Data[2] = 0xFF;
		gCanBusCtl1.TxMsg.Data[3] = 0xFF;
		gCanBusCtl1.TxMsg.Data[4] = 4;
		gCanBusCtl1.TxMsg.Data[5] = 0;
		gCanBusCtl1.TxMsg.DLC  = 6;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);
		
		//Ack
		gExCom.TxdBuf[0] = 0x5C;
		gExCom.TxdBuf[1] = 0xf3;
		gExCom.TxdBuf[2] = gExCom.ADS;
		gExCom.TxdBuf[3] = 0xFF;// UID1
		gExCom.TxdBuf[4] = 0xFF;
		gExCom.TxdBuf[5] = 0xFF;
		gExCom.TxdBuf[6] = 0xFF;
		gExCom.TxdBuf[7] = 0;
		gExCom.TxdBuf[8] = 0;
		gExCom.TxdBuf[9] = 0;
		gExCom.TxdBuf[10] = 0;
		gExCom.TxdBuf[11] = 0;
		gExCom.TxdBuf[12] = 0;
		gExCom.TxdBuf[13] = 0;
		gExCom.TxdBuf[14] = 0;
		gExCom.TxdBuf[15] = 0;
		gExCom.TxdBuf[16] = 0;
		gExCom.TxdBuf[17] = 0;
		gExCom.TxdBuf[18] = 0;

		temp = check_crc16(gExCom.TxdBuf, 19);
		gExCom.TxdBuf[19] = temp>>8;
		gExCom.TxdBuf[20] = temp&0xff;

		gExCom.TxdFlag = 1;
		gExCom.TxdLen = 21;
		gExCom.TxdDly = 5;	
	}




}

//参数
static void _parse_data_dx(u8 idx)
{

	u16 temp = 0;

	//配置参数
	if(idx == 0)
	{
		gSysPar.INIT = gExCom.RecBuf[3];
		gSysPar.CTL = gExCom.RecBuf[4];
		gSysPar.MTOR = (gExCom.RecBuf[5]<<8) + gExCom.RecBuf[6];
		gSysPar.KPP = (gExCom.RecBuf[7]<<8) + gExCom.RecBuf[8];
		gSysPar.KVP = (gExCom.RecBuf[9]<<8) + gExCom.RecBuf[10];
		gSysPar.KVI = (gExCom.RecBuf[11]<<8) + gExCom.RecBuf[12];
		gSysPar.HHD = (gExCom.RecBuf[13]<<8) + gExCom.RecBuf[14];
		gSysPar.ZT_MidOfs = (s16)((gExCom.RecBuf[15]<<8) + gExCom.RecBuf[16]);
		gSysPar.LEN = (gExCom.RecBuf[17]<<8) + gExCom.RecBuf[18];
		gSysPar.LEN_StopSB = gExCom.RecBuf[19];
		gSysPar.DJ_Spd = gExCom.RecBuf[20];
		gSysPar.DSPC = (gExCom.RecBuf[21]<<8) + gExCom.RecBuf[22];
		gSysPar.DSPC_Rto = gExCom.RecBuf[23];
		gSysPar.DSPC_FD_RTO = gExCom.RecBuf[24];
		gSysPar.DSPC_FD_Period = gExCom.RecBuf[25];
		gSysPar.DJ_Ofs = (s8)gExCom.RecBuf[26];
		gSysPar.RunTime = (gExCom.RecBuf[27]<<8) + gExCom.RecBuf[28];
		gSysPar.ACC = gExCom.RecBuf[29];
		gSysPar.DEC = gExCom.RecBuf[30];
		gSysPar.SB_W = (gExCom.RecBuf[31]<<8) + gExCom.RecBuf[32];
		gSysPar.SB_Rto = gExCom.RecBuf[33];
		gSysPar.RB_Mode = gExCom.RecBuf[34];
		gSysPar.RB1_W = (gExCom.RecBuf[35]<<8) + gExCom.RecBuf[36];
		gSysPar.RB1_S = gExCom.RecBuf[37];
		gSysPar.RB1_L = gExCom.RecBuf[38];
		gSysPar.RB2_W = (gExCom.RecBuf[39]<<8) + gExCom.RecBuf[40];
		gSysPar.RB2_S = gExCom.RecBuf[41];
		gSysPar.RB2_T = gExCom.RecBuf[42];
		gSysPar.LT_Time = gExCom.RecBuf[43];
		gSysPar.LT_Ofs = gExCom.RecBuf[44];
		gSysPar.DJ_Ofs_O = gExCom.RecBuf[45];
		gSysPar.DJ_Time = gExCom.RecBuf[46];
		gSysPar.YS_Spd = (gExCom.RecBuf[47]<<8) + gExCom.RecBuf[48];
		gSysPar.YS_Dir = gExCom.RecBuf[49];
		gSysPar.DJ_Ofs_BC = (s8)gExCom.RecBuf[50];


		
		gExCom.ParRequestFlag = 0;//清除参数请求标志
		gExCom.ParRxFlag = 0x1;//接收到参数
		gExCom.ParTransDlyCnt = 200;

		

		//Ack
		gExCom.TxdBuf[0] = 0x5C;
		gExCom.TxdBuf[1] = 0xd0;
		gExCom.TxdBuf[2] = gExCom.ADS;
		gExCom.TxdBuf[3] = 0;
		gExCom.TxdBuf[4] = 0;
		gExCom.TxdBuf[5] = 0;
		gExCom.TxdBuf[6] = 0;
		gExCom.TxdBuf[7] = 0;
		gExCom.TxdBuf[8] = 0;
		gExCom.TxdBuf[9] = 0;
		gExCom.TxdBuf[10] = 0;
		gExCom.TxdBuf[11] = 0;
		gExCom.TxdBuf[12] = 0;
		gExCom.TxdBuf[13] = 0;
		gExCom.TxdBuf[14] = 0;
		gExCom.TxdBuf[15] = 0;
		gExCom.TxdBuf[16] = 0;
		gExCom.TxdBuf[17] = 0;
		gExCom.TxdBuf[18] = 0;

		temp = check_crc16(gExCom.TxdBuf, 19);
		gExCom.TxdBuf[19] = temp>>8;
		gExCom.TxdBuf[20] = temp&0xff;

		gExCom.TxdFlag = 1;
		gExCom.TxdLen = 21;
		gExCom.TxdDly = 5;	
		
	}

	//回读参数-- 屏不存储参数
	if(idx == 1)
	{
	}


}


//读单锭参数
static void _parse_data_ex(u8 idx)
{


	u16 temp = 0;

	if(idx >= MAX_NODE_NUM)
		return;

	if(gExCom.PAR_ReadFlag == 0)
	{
		gExCom.PAR_ReadFlag = 1;
		gExCom.PAR_ID = idx+1;

	}
	else if(gExCom.PAR_ReadFlag == 3)
	{
		gExCom.PAR_ReadFlag = 0;
		gExCom.PAR_ReadDlyCnt =0;
		gExCom.PAR_ID = 0;
		//Ack
		gExCom.TxdBuf[0] = 0x5c;
		gExCom.TxdBuf[1] = 0xe0+idx;
		gExCom.TxdBuf[2] = gExCom.ADS;
		gExCom.TxdBuf[3]	= gSysPar_RdBack.INIT&0xff;
		gExCom.TxdBuf[4] =gSysPar_RdBack.CTL&0xff;
		gExCom.TxdBuf[5] = gSysPar_RdBack.MTOR>>8;
		gExCom.TxdBuf[6] = gSysPar_RdBack.MTOR&0xff;
		gExCom.TxdBuf[7] = gSysPar_RdBack.KPP>>8;
		gExCom.TxdBuf[8] = gSysPar_RdBack.KPP&0xff;
		gExCom.TxdBuf[9] = gSysPar_RdBack.KVP>>8;
		gExCom.TxdBuf[10] = gSysPar_RdBack.KVP&0xff;
		gExCom.TxdBuf[11] = gSysPar_RdBack.KVI>>8;
		gExCom.TxdBuf[12] = gSysPar_RdBack.KVI&0xff;
		gExCom.TxdBuf[13] = gSysPar_RdBack.HHD>>8;
		gExCom.TxdBuf[14] = gSysPar_RdBack.HHD&0xff;
		gExCom.TxdBuf[15] = gSysPar_RdBack.ZT_MidOfs>>8;
		gExCom.TxdBuf[16] = gSysPar_RdBack.ZT_MidOfs&0xff;
		gExCom.TxdBuf[17] = gSysPar_RdBack.LEN>>8;
		gExCom.TxdBuf[18] = gSysPar_RdBack.LEN&0xff;
		gExCom.TxdBuf[19] =gSysPar_RdBack.LEN_StopSB&0xff;
		gExCom.TxdBuf[20] =gSysPar_RdBack.DJ_Spd&0xff;
		gExCom.TxdBuf[21] = gSysPar_RdBack.DSPC>>8;
		gExCom.TxdBuf[22] = gSysPar_RdBack.DSPC&0xff;
		gExCom.TxdBuf[23] =gSysPar_RdBack.DSPC_Rto&0xff;
		gExCom.TxdBuf[24] =gSysPar_RdBack.DSPC_FD_RTO&0xff;
		gExCom.TxdBuf[25] =gSysPar_RdBack.DSPC_FD_Period&0xff;
		gExCom.TxdBuf[26] =(s8)gSysPar_RdBack.DJ_Ofs;
		gExCom.TxdBuf[27] = gSysPar_RdBack.RunTime>>8;
		gExCom.TxdBuf[28] = gSysPar_RdBack.RunTime&0xff;
		gExCom.TxdBuf[29] =gSysPar_RdBack.ACC&0xff;
		gExCom.TxdBuf[30] =gSysPar_RdBack.DEC&0xff;
		gExCom.TxdBuf[31] = gSysPar_RdBack.SB_W>>8;
		gExCom.TxdBuf[32] = gSysPar_RdBack.SB_W&0xff;
		gExCom.TxdBuf[33] =gSysPar_RdBack.SB_Rto&0xff;
		gExCom.TxdBuf[34] =gSysPar_RdBack.RB_Mode&0xff;
		gExCom.TxdBuf[35] = gSysPar_RdBack.RB1_W>>8;
		gExCom.TxdBuf[36] = gSysPar_RdBack.RB1_W&0xff;
		gExCom.TxdBuf[37] =gSysPar_RdBack.RB1_S&0xff;
		gExCom.TxdBuf[38] =gSysPar_RdBack.RB1_L&0xff;
		gExCom.TxdBuf[39] = gSysPar_RdBack.RB2_W>>8;
		gExCom.TxdBuf[40] = gSysPar_RdBack.RB2_W&0xff;
		gExCom.TxdBuf[41] =gSysPar_RdBack.RB2_S&0xff;
		gExCom.TxdBuf[42] =gSysPar_RdBack.RB2_T &0xff;
		gExCom.TxdBuf[43] =gSysPar_RdBack.LT_Time&0xff;
		gExCom.TxdBuf[44] =gSysPar_RdBack.LT_Ofs &0xff;
		gExCom.TxdBuf[45] =gSysPar_RdBack.DJ_Ofs_O&0xff;
		gExCom.TxdBuf[46] =gSysPar_RdBack.DJ_Time &0xff;
		gExCom.TxdBuf[47] = gSysPar_RdBack.YS_Spd>>8;
		gExCom.TxdBuf[48] = gSysPar_RdBack.YS_Spd&0xff;
		gExCom.TxdBuf[49] =gSysPar_RdBack.YS_Dir &0xff;
		gExCom.TxdBuf[50] =(s8)gSysPar_RdBack.DJ_Ofs_BC;
		gExCom.TxdBuf[51] = 0;
		gExCom.TxdBuf[52] = 0;
		gExCom.TxdBuf[53] = 0;
		gExCom.TxdBuf[54] = 0;
		gExCom.TxdBuf[55] = 0;
		gExCom.TxdBuf[56] = 0;
		gExCom.TxdBuf[57] = 0;
		gExCom.TxdBuf[58] = 0;
		gExCom.TxdBuf[59] = 0;
		gExCom.TxdBuf[60] = 0;

		temp = check_crc16(gExCom.TxdBuf, 61);
		gExCom.TxdBuf[61] = temp>>8;
		gExCom.TxdBuf[62] = temp&0xff;

		gExCom.TxdFlag = 1;
		gExCom.TxdLen = 63;
		gExCom.TxdDly = 5;
	}

}


static void _parse_data_cx(u8 idx)
{
	u8 temp = 0;
	u8 ID = 0;

	if(gExCom.RecBuf[3] < 1 ||gExCom.RecBuf[3]>MAX_NODE_NUM)
		return ;

	ID = gExCom.RecBuf[3];

	//参数初始化
	if(gExCom.RecBuf[4] == 0xa8)
	{
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = (0<< 16) + (CAN_CMD_CTL<<8) + ID;
		gCanBusCtl1.TxMsg.Data[0] = 2;
		gCanBusCtl1.TxMsg.DLC  = 1;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);

	}
	//时间清零
	if(gExCom.RecBuf[4] == 0x68)
	{
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = (0<< 16) + (CAN_CMD_CTL<<8) + ID;
		gCanBusCtl1.TxMsg.Data[0] = 3;
		gCanBusCtl1.TxMsg.DLC  = 1;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);

	}
	//报警清零
	if(gExCom.RecBuf[4] == 0x79)
	{
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = (0<< 16) + (CAN_CMD_CTL<<8) + ID;
		gCanBusCtl1.TxMsg.Data[0] = 4;
		gCanBusCtl1.TxMsg.DLC  = 1;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);

	}
	//启动
	if(gExCom.RecBuf[4] == 0x8a)
	{
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = (0<< 16) + (CAN_CMD_CTL<<8) + ID;
		gCanBusCtl1.TxMsg.Data[0] = 1;
		gCanBusCtl1.TxMsg.DLC  = 1;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);

	}
	//停机
	if(gExCom.RecBuf[4] == 0x9b)
	{
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = (0<< 16) + (CAN_CMD_CTL<<8) + ID;
		gCanBusCtl1.TxMsg.Data[0] = 0;
		gCanBusCtl1.TxMsg.DLC  = 1;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);

	}



	idx = ID-1;
	//Ack
	gExCom.TxdBuf[0] = 0x5c;
	gExCom.TxdBuf[1] = 0xc0;
	gExCom.TxdBuf[2] = gExCom.ADS;
	gExCom.TxdBuf[3]	= gExCom.RecBuf[3];
	gExCom.TxdBuf[4] =gStsVal[idx].HD_Spd<<8;
	gExCom.TxdBuf[5] = gStsVal[idx].HD_Spd&0xff;
	gExCom.TxdBuf[6] = 0;
	gExCom.TxdBuf[7] = 0;
	gExCom.TxdBuf[8] = 0;
	gExCom.TxdBuf[9] = 0;
	gExCom.TxdBuf[10] = gStsVal[idx].ErrL;
	gExCom.TxdBuf[11] = gStsVal[idx].ErrR;
	gExCom.TxdBuf[12] = gStsVal[idx].RunTimeCur>>8;
	gExCom.TxdBuf[13] = gStsVal[idx].RunTimeCur&0xff;
	gExCom.TxdBuf[14] = gStsVal[idx].DSPC>>8;
	gExCom.TxdBuf[15] = gStsVal[idx].DSPC&0xff;
	gExCom.TxdBuf[16] = gStsVal[idx].Sts;
	gExCom.TxdBuf[17] = gStsVal[idx].Err;
	gExCom.TxdBuf[18] = gStsVal[idx].Verson_App;
	gExCom.TxdBuf[19] = gStsVal[idx].Verson_Boot;
	gExCom.TxdBuf[20] = gStsVal[idx].CurLEN>>8;
	gExCom.TxdBuf[21] = gStsVal[idx].CurLEN&0xff;
	gExCom.TxdBuf[22] = 0;
	gExCom.TxdBuf[23] = 0;
	gExCom.TxdBuf[24] = 0;
	gExCom.TxdBuf[25] = 0;
	gExCom.TxdBuf[26] = 0;
	gExCom.TxdBuf[27] = 0;
	gExCom.TxdBuf[28] = 0;
	gExCom.TxdBuf[29] = 0;
	gExCom.TxdBuf[30] = 0;
	gExCom.TxdBuf[31] = 0;
	gExCom.TxdBuf[32] = 0;
	gExCom.TxdBuf[33] = 0;
	gExCom.TxdBuf[34] = 0;
	gExCom.TxdBuf[35] = 0;
	gExCom.TxdBuf[36] = 0;
	gExCom.TxdBuf[37] = 0;
	gExCom.TxdBuf[38] = 0;
	gExCom.TxdBuf[39] = 0;
	gExCom.TxdBuf[40] = 0;
	gExCom.TxdBuf[41] = 0;
	gExCom.TxdBuf[42] = 0;
	gExCom.TxdBuf[43] = 0;

	temp = check_crc16(gExCom.TxdBuf, 44);
	gExCom.TxdBuf[44] = temp>>8;
	gExCom.TxdBuf[45] = temp&0xff;

	gExCom.TxdFlag = 1;
	gExCom.TxdLen = 46;
	gExCom.TxdDly = 5;

}




static u8 _send_intervl(u8 *dp)
{
	static u16 n=0;
	u8 sci_state =0;
	
	if(gExCom.TxdSts == 0)//发送数据
	{
		SCI_B_DE_CTL(USART_BUS_TXD);
		n = 0;
		gExCom.TxdSts = 1;
	}else if(gExCom.TxdSts==1)//等待发送完成
	{
		USARTB_TXD(dp[n]);
		gExCom.TxdSts = 2;
		n++;
		gExCom.TxdErr = 0;
	}
	else if(gExCom.TxdSts==2)//等待发送完成
	{
		sci_state = USARTB_TXD_OK();
		if(sci_state)//发送完成单个字节
		{
			if(n>=gExCom.TxdLen)//发送完成
			{
				gExCom.TxdSts = 0;
				n = 0;
				SCI_B_DE_CTL(USART_BUS_RXD);
				return 1;
			}else{
				gExCom.TxdSts = 1;
			}
		}
		else
		{
			gExCom.TxdErr ++;
			if(gExCom.TxdErr  > 1000)
			{
				gExCom.TxdErr  = 0;
				SCI_B_DE_CTL(USART_BUS_RXD);
				return 2;
			}
		}
	}
	return 0;		
}




void excom_init(void)
{
	memset(&gExCom, 0, sizeof(ExCom_t));
	gExCom.ADS = 1;
	gExCom.RxdLen =  21;
	gExCom.ParRequestFlag = 1;

	


}


void excom_rx(u8 temp)
{
	if(gExCom.RxdFlag) 
	{
		// 上一帧数据未处理
		return;
	}


	//--------------------------------------------------------------//
	//长度判断	
	if(gExCom.RxdIndex>= gExCom.RxdLen && gExCom.RxdLen){
		gExCom.RxdIndex= 0;
	}
	if(gExCom.RxdTicker == 0 && gExCom.RxdIndex)
	{
		gExCom.RxdIndex= 0;
	}
	gExCom.RxdTicker = 5*SYS_ISR_PSC;
	//--------------------------------------------------------------//	
	
	//--------------------------------------------------------------//
	//数据缓存	
	gExCom.RecBuf[gExCom.RxdIndex] = temp;
	//--------------------------------------------------------------//

	//--------------------------------------------------------------//
	//头码判断
	if(gExCom.RecBuf[0] != 0xC5)
	{
		gExCom.RxdIndex= 0;
		return;
	}
	else if(gExCom.RxdIndex== 2)
	{
		if(gExCom.RecBuf[2] !=gExCom.ADS)
		{
			gExCom.RxdIndex= 0;
			return;
		}
		else
		{		
			if(gExCom.RecBuf[1] == EXCMD_F0)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_F1)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_F2)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_F3)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_D0)gExCom.RxdLen =  63;
			else if(gExCom.RecBuf[1] == EXCMD_E0)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E1)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E2)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E3)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E4)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E5)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E6)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E7)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E8)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_E9)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_EA)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_EB)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_D1)gExCom.RxdLen =  21;
			else if(gExCom.RecBuf[1] == EXCMD_C0)gExCom.RxdLen =  21;
			else
			{
				gExCom.RxdLen =  21;
			}


		}
	}

	else if(gExCom.RxdIndex== gExCom.RxdLen-1&& gExCom.RxdIndex >3)
	{

		gExCom.RxdFlag = TRUE;
		gExCom.RxdIndex = 0;
	}
	
	gExCom.RxdIndex++;
	
}






void excom_tx(u16 len)
{
	if(gExCom.TxdSts == 0)//发送数据
	{
		SCI_B_DE_CTL(USART_BUS_TXD);
		gExCom.TxdSts = 1;
	}
	else if(gExCom.TxdSts==1)//等待发送完成
	{
		USARTB_TC_CLR();           // 清发送完成状态
		USARTB_TXD(gExCom.TxdBuf[0]);
		 
		gExCom.TxdCnt = 0;
		gExCom.TxdLen = len;	
		gExCom.TxdSts = 2;
	}
	else
	{
	
	}



}

// 1ms 在主循环执行一次
void excom_task(void)
{
	u16 temp = 0;
	u16 crc_check = 0;
	
	
	if(gExCom.TxdFlag)
	{	

		if(gExCom.TxdDly)
		{
			SCI_B_DE_CTL(USART_BUS_TXD);			
		}
		else
		{
			excom_tx(gExCom.TxdLen);
		}
		
		return;

	}





	//接受到新的参数，延迟结束后转发到单锭
	if(gExCom.ParRxFlag && gExCom.ParTransDlyCnt==0)
	{
		gExCom.ParOk ++;
		gExCom.ParRxFlag = 0;
		gExCom.ParSave = 1;
		gExCom.ParSaveDlyCnt = 1000;

		for(temp = 0;temp < MAX_NODE_NUM; temp ++)
			gCanBusCtl1.DataRequestMain[temp] = 1;

	}
	else if(gExCom.ParTransDlyCnt)
	{
		gExCom.ParTransDlyCnt--;
	}	

	//参数保存
	if(gExCom.ParSave && gExCom.ParSaveDlyCnt == 0)
	{
		gExCom.ParSave = 0;
		gSysCtlVar.ParSave_Flag= 1;
	}
	else if(gExCom.ParSaveDlyCnt)
	{
		gExCom.ParSaveDlyCnt=1;
	}

	//UID 读取处理
	if(gExCom.UID_ReadFlag && gExCom.UID_ReadDlyCnt == 0)
	{
		gExCom.UID_ReadFlag =0;
	}
	else if(gExCom.UID_ReadDlyCnt)
	{
		gExCom.UID_ReadDlyCnt--;
	}

	//参数回读
	if(gExCom.PAR_ReadFlag == 1)
	{ 
		gExCom.PAR_ReadDlyCnt =200;
		gCanBusCtl1.Flg_ParReadMask = 0;//清除回读标志
		memset(&gSysPar_RdBack, 0, sizeof(SysPar_t));
		//发送数据
		gCanBusCtl1.TxMsg.ExtId = (0<< 16) + (CAN_CMD_READ_PAR<<8) + (gExCom.PAR_ID);
		gCanBusCtl1.TxMsg.Data[0] = 0;
		gCanBusCtl1.TxMsg.DLC  = 1;
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);
	
	}	
	else	if(gExCom.PAR_ReadFlag == 2)
	{
		if(gExCom.PAR_ReadDlyCnt)
			gExCom.PAR_ReadDlyCnt--;
		else
			gExCom.PAR_ReadFlag = 3;//超时
	}
	else	if(gExCom.PAR_ReadFlag == 3)
	{
		_parse_data_ex(gExCom.PAR_ID-1);
	}

		
	// 等待接收完成
	if(gExCom.RxdFlag == FALSE){
		return;
	}
	gExCom.rx_ok ++;



	//判断校验码是否正确
	crc_check = check_crc16(gExCom.RecBuf,gExCom.RxdLen-2);
	if(crc_check !=((gExCom.RecBuf[gExCom.RxdLen-2]<<8) + gExCom.RecBuf[gExCom.RxdLen-1]))
	{
		
		goto LoopErrEnd;
	}

	gExCom.chk_ok ++;
	gExCom.ConnectFlag= FALSE;
	gExCom.ConnectTicker = 0;		

	switch(gExCom.RecBuf[1])
	{
	case EXCMD_F0: _parse_data_fx(0);	break;
	case EXCMD_F1: _parse_data_fx(1);	break;
	case EXCMD_F2: _parse_data_fx(2);	break;
	case EXCMD_F3: _parse_data_fx(3);	break;
	case EXCMD_E0: _parse_data_ex(0);break;
	case EXCMD_E1: _parse_data_ex(1);break;
	case EXCMD_E2: _parse_data_ex(2);break;
	case EXCMD_E3: _parse_data_ex(3);break;
	case EXCMD_E4: _parse_data_ex(4);break;
	case EXCMD_E5: _parse_data_ex(5);break;
	case EXCMD_E6: _parse_data_ex(6);break;
	case EXCMD_E7: _parse_data_ex(7);break;
	case EXCMD_E8: _parse_data_ex(8);break;
	case EXCMD_E9: _parse_data_ex(9);break;
	case EXCMD_EA: _parse_data_ex(10);break;
	case EXCMD_EB: _parse_data_ex(11);break;
	case EXCMD_D0: _parse_data_dx(0);break;
	case EXCMD_D1: _parse_data_dx(1);break;
	case EXCMD_C0: _parse_data_cx(0);break;
	default:break;
	}



	
	
	if(gExCom.TxdFlag)
		return ;

LoopErrEnd:	
	memset(gExCom.RecBuf,0,100);
	gExCom.RxdFlag = 0;
	gExCom.RxdIndex = 0;
}
/***************************************************************/

