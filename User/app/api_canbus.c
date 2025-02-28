#include "sys_include.h"

CanBusCtl_t gCanBusCtl1 = {0, };


StsVal_t gStsVal[MAX_NODE_NUM] = {0, };
SysPar_t gSysPar_RdBack = {0, };


void can_msg_parse(CanMsg_t *pMsg)
{
	u8 cmd = 0;
	u8 ads = 0;
	u8 idx = 0;
	u8 node_idx = 0;
	

	//配置ID 信息回复
	if(pMsg->ExtId == 1)
	{
		//搜集UID 信息
		if(pMsg->Data[4] == 1)
		{
			if(gCanBusCtl1.UID_Idx < MAX_NODE_NUM)
			{
				gCanBusCtl1.UID[gCanBusCtl1.UID_Idx] = (pMsg->Data[3]<<24)+  (pMsg->Data[2]<<16)+ (pMsg->Data[1]<<8) + pMsg->Data[0];
				gCanBusCtl1.ID[gCanBusCtl1.UID_Idx] = pMsg->Data[5];
				gCanBusCtl1.UID_Idx++;
			}
		}
		//握手帧回复
		else if(pMsg->Data[4] == 2)
		{
		}
		//配置帧回复
		else if(pMsg->Data[4] == 3)
		{
		}

	
		return ;
	}
	
	idx = (pMsg->ExtId>>16)&0x7F;
	cmd = (pMsg->ExtId>>8)&0xFF;
	ads = pMsg->ExtId&0xFF;

	if(ads < 1 || ads > MAX_NODE_NUM)
		return ;
	node_idx =ads-1;


		
	switch (cmd)
	{
	
	case CAN_CMD_SET_PAR_ACK:
		if(gCanBusCtl1.State == STS_WAIT_OVER_TIME)
		{
			gCanBusCtl1.RxFlag  = 2;
		}

		break;
	case CAN_CMD_CTL_ACK:
	

		break;
	case CAN_CMD_READ_PAR_ACK:
		if(idx == 0)
		{
			gSysPar_RdBack.INIT = pMsg->Data[0];
			gSysPar_RdBack.CTL = pMsg->Data[1];
			gSysPar_RdBack.MTOR = (pMsg->Data[3]<<8) + pMsg->Data[2];
			gSysPar_RdBack.KPP = (pMsg->Data[5]<<8) + pMsg->Data[4];
			gSysPar_RdBack.KVP = (pMsg->Data[7]<<8) + pMsg->Data[6];
			gCanBusCtl1.Flg_ParReadMask  |= 0x1;
		}
		else if(idx == 1)
		{
			gSysPar_RdBack.KVI = (pMsg->Data[1]<<8) + pMsg->Data[0];
			gSysPar_RdBack.HHD =(pMsg->Data[3]<<8) + pMsg->Data[2];
			gSysPar_RdBack.ZT_MidOfs = (s16)((pMsg->Data[5]<<8) + pMsg->Data[4]);
			gSysPar_RdBack.LEN = (pMsg->Data[7]<<8) + pMsg->Data[6];
			gCanBusCtl1.Flg_ParReadMask  |= 0x2;

		}
		else if(idx == 2)
		{
			gSysPar_RdBack.LEN_StopSB = pMsg->Data[0];
			gSysPar_RdBack.DJ_Spd = pMsg->Data[1];
			gSysPar_RdBack.DSPC = (pMsg->Data[3]<<8) + pMsg->Data[2];
			gSysPar_RdBack.DSPC_Rto= pMsg->Data[4];
			gSysPar_RdBack.DSPC_FD_RTO = pMsg->Data[5];
			gSysPar_RdBack.DSPC_FD_Period= pMsg->Data[6];
			gSysPar_RdBack.DJ_Ofs = (s8)pMsg->Data[7];
			gCanBusCtl1.Flg_ParReadMask  |= 0x4;

		}
		else if(idx == 3)
		{
			gSysPar_RdBack.RunTime =  (pMsg->Data[1]<<8) + pMsg->Data[0];
			gSysPar_RdBack.ACC = pMsg->Data[2]*10;
			gSysPar_RdBack.DEC = pMsg->Data[3]*10;
			gSysPar_RdBack.SB_W=  (pMsg->Data[5]<<8) + pMsg->Data[4];
			gSysPar_RdBack.SB_Rto = pMsg->Data[6];
			gSysPar_RdBack.RB_Mode = pMsg->Data[7];
			gCanBusCtl1.Flg_ParReadMask  |= 0x8;

		}
		else if(idx == 4)
		{
			gSysPar_RdBack.RB1_W = (pMsg->Data[1]<<8) + pMsg->Data[0];
			gSysPar_RdBack.RB1_S = pMsg->Data[2];
			gSysPar_RdBack.RB1_L = pMsg->Data[3];
			gSysPar_RdBack.RB2_W =  (pMsg->Data[5]<<8) + pMsg->Data[4];
			gSysPar_RdBack.RB2_S = pMsg->Data[6];
			gSysPar_RdBack.RB2_T = pMsg->Data[7];
			gCanBusCtl1.Flg_ParReadMask  |= 0x10;

		}
		else if(idx == 5)
		{
			gSysPar_RdBack.LT_Ofs = pMsg->Data[0];
			gSysPar_RdBack.LT_Time = pMsg->Data[1];
			gSysPar_RdBack.DJ_Ofs_O = pMsg->Data[2];
			gSysPar_RdBack.DJ_Time = pMsg->Data[3];
			gSysPar_RdBack.YS_Spd = (pMsg->Data[5]<<8) + pMsg->Data[4];
			gSysPar_RdBack.YS_Dir = pMsg->Data[6];
			gSysPar_RdBack.DJ_Ofs_BC = (s8)pMsg->Data[7];
			gCanBusCtl1.Flg_ParReadMask  |= 0x20;

		}
		if(gCanBusCtl1.Flg_ParReadMask == 0x003F)//有所有的都接收完了
		{
			gExCom.PAR_ReadFlag  = 3;

		}
		break;
	case CAN_CMD_STATUS1_ACK:
		if(idx == 0)
		{
			gStsVal[node_idx].HD_Spd = (s16)((pMsg->Data[1]<<8) + pMsg->Data[0]);
			gStsVal[node_idx].HD_PosCur = (s32)((pMsg->Data[5]<<24) + (pMsg->Data[4]<<16) + (pMsg->Data[3]<<8)+ pMsg->Data[2]);
			gStsVal[node_idx].ErrL = (s8)pMsg->Data[6];
			gStsVal[node_idx].ErrR = (s8)pMsg->Data[7];
			gCanBusCtl1.Flg_StsReadMask[node_idx]  |= 0x1;
		}
		else if(idx == 1)
		{
			gStsVal[node_idx].RunTimeCur = (pMsg->Data[2]<<16)+ (pMsg->Data[1]<<8) + pMsg->Data[0];
			gStsVal[node_idx].DSPC = (pMsg->Data[5]<<8)+ pMsg->Data[4];
			gStsVal[node_idx].Sts = pMsg->Data[6];
			gStsVal[node_idx].Err = pMsg->Data[7];
			gCanBusCtl1.Flg_StsReadMask[node_idx]  |= 0x2;
		}
		else if(idx == 2)
		{
			gCanBusCtl1.DataRequestMain[node_idx] = pMsg->Data[0]?1:0;
			gStsVal[node_idx].Verson_App = pMsg->Data[1];
			gStsVal[node_idx].CurLEN = (pMsg->Data[3]<<8)+ pMsg->Data[2];
			gStsVal[node_idx].Verson_Boot = pMsg->Data[1];
			gCanBusCtl1.Flg_StsReadMask[node_idx]  |= 0x4;
		}
		else if(idx == 3)
		{
			gStsVal[node_idx].SG_PosCur = (s32)((pMsg->Data[3]<<24) + (pMsg->Data[2]<<16) + (pMsg->Data[1]<<8)+ pMsg->Data[0]);
			gCanBusCtl1.Flg_StsReadMask[node_idx]  |= 0x8;
		}
		if(gCanBusCtl1.Flg_ParReadMask == 0x00F)
		{
			if(gCanBusCtl1.State == STS_WAIT_OVER_TIME)
			{
				gCanBusCtl1.RxFlag  = 2;
			}

		}

		break;
	case CAN_CMD_SET_CURTIME_ACK:
		break;
	case CAN_CMD_POS_ACK:
		break;
		
	default:break;
	}

	

}



void can1_task(void)
{
	static u8 psr = 0;
	u32 ID = 0;
	u32 CMD = 0;
	u32 IDX = 0;
	u8 tmp = 0;
	u8 tmp1= 0;
	CanMsg_t* pBuf = NULL;

	psr++;
	if(psr < SYS_ISR_PSC)
		return;
	psr = 0;
	

	//初始化
	if(gCanBusCtl1.State == STS_INIT)
	{
		gCanBusCtl1.State = 0;
		gCanBusCtl1.CurNode = 0;
		gCanBusCtl1.CurIndex = 0;
		gCanBusCtl1.ReSendCnt = MAX_RESEND_NUM;

		gCanBusCtl1.State = STS_LOAD;
	}
	//连续数据发送等待
	else	if(gCanBusCtl1.State == STS_WAIT_SEND)
	{
		if(gCanBusCtl1.WaitCnt)gCanBusCtl1.WaitCnt--;
		else 
		{
			gCanBusCtl1.CurIndex++;
			gCanBusCtl1.State = STS_LOAD;
		}
	}
	//超时等待
	else if(gCanBusCtl1.State == STS_WAIT_OVER_TIME)
	{
		if(gCanBusCtl1.WaitCnt)gCanBusCtl1.WaitCnt--;
		if(gCanBusCtl1.WaitCnt == 0)
		{
			gCanBusCtl1.State = STS_OVER_TIME;
		}

		//部分收到，超时重发处理
		if(gCanBusCtl1.RxFlag == 1)
		{
			gCanBusCtl1.State = STS_OVER_TIME;
		}
		//全部收到
		else if(gCanBusCtl1.RxFlag == 2)
		{
			gCanBusCtl1.State = STS_PARSE;

		}

	}
	//加载发送数据
	else if(gCanBusCtl1.State == STS_LOAD)
	{	
		//数据请求或者有更新
		if(gCanBusCtl1.DataRequestMain[gCanBusCtl1.CurNode])
		{
			gCanBusCtl1.CurCmd = CAN_CMD_SET_PAR;  //单节控制参数
			gCanBusCtl1.MaxIndex = 5;
			gCanBusCtl1.RxFlag  = 0;
			if(gCanBusCtl1.CurIndex == gCanBusCtl1.MaxIndex)// 最后一帧  IDX = 0xFFFF
			{
				gCanBusCtl1.FinalFrame = 1;
			}
			else 
			{
				gCanBusCtl1.FinalFrame = 0;
			}
			ID = gCanBusCtl1.CurID = gCanBusCtl1.CurNode+1;
			CMD  = gCanBusCtl1.CurCmd;
			IDX = gCanBusCtl1.CurIndex;

			gCanBusCtl1.TxMsg.ExtId = (IDX<< 16) + (CMD<<8) + gCanBusCtl1.CurID;
			if(IDX == 0)
			{
				gCanBusCtl1.TxMsg.Data[0] = gSysPar.INIT&0xff;
				gCanBusCtl1.TxMsg.Data[1] = gSysPar.CTL&0xff;
				gCanBusCtl1.TxMsg.Data[2] = gSysPar.MTOR&0xff;
				gCanBusCtl1.TxMsg.Data[3] = gSysPar.MTOR>>8;
				gCanBusCtl1.TxMsg.Data[4] = gSysPar.KPP&0xff;
				gCanBusCtl1.TxMsg.Data[5] = gSysPar.KPP>>8;
				gCanBusCtl1.TxMsg.Data[6] = gSysPar.KVP&0xff;
				gCanBusCtl1.TxMsg.Data[7] = gSysPar.KVP>>8;
				gCanBusCtl1.TxMsg.DLC  = 8;
			}
			else if(IDX == 1)
			{
				gCanBusCtl1.TxMsg.Data[0] = gSysPar.KVI&0xff;
				gCanBusCtl1.TxMsg.Data[1] = gSysPar.KVI>>8;
				gCanBusCtl1.TxMsg.Data[2] = gSysPar.HHD&0xff;
				gCanBusCtl1.TxMsg.Data[3] = gSysPar.HHD>>8;
				gCanBusCtl1.TxMsg.Data[4] = gSysPar.ZT_MidOfs&0xff;
				gCanBusCtl1.TxMsg.Data[5] = gSysPar.ZT_MidOfs>>8;
				gCanBusCtl1.TxMsg.Data[6] = gSysPar.LEN&0xff;
				gCanBusCtl1.TxMsg.Data[7] = gSysPar.LEN>>8;
				gCanBusCtl1.TxMsg.DLC  = 8;
			}
			else if(IDX == 2)
			{
				gCanBusCtl1.TxMsg.Data[0] = gSysPar.LEN_StopSB&0xff;
				gCanBusCtl1.TxMsg.Data[1] = gSysPar.DJ_Spd&0xff;
				gCanBusCtl1.TxMsg.Data[2] = gSysPar.DSPC&0xff;
				gCanBusCtl1.TxMsg.Data[3] = gSysPar.DSPC>>8;
				gCanBusCtl1.TxMsg.Data[4] = gSysPar.DSPC_Rto&0xff;
				gCanBusCtl1.TxMsg.Data[5] = gSysPar.DSPC_FD_RTO&0xff;
				gCanBusCtl1.TxMsg.Data[6] = gSysPar.DSPC_FD_Period&0xff;
				gCanBusCtl1.TxMsg.Data[7] = gSysPar.DJ_Ofs&0xff;
				gCanBusCtl1.TxMsg.DLC  = 8;
			}
			else if(IDX == 3)
			{
				gCanBusCtl1.TxMsg.Data[0] = gSysPar.RunTime&0xff;
				gCanBusCtl1.TxMsg.Data[1] = gSysPar.RunTime>>8;
				gCanBusCtl1.TxMsg.Data[2] = gSysPar.ACC&0xff;
				gCanBusCtl1.TxMsg.Data[3] = gSysPar.DEC&0xff;
				gCanBusCtl1.TxMsg.Data[4] = gSysPar.SB_W&0xff;
				gCanBusCtl1.TxMsg.Data[5] = gSysPar.SB_W>>8;
				gCanBusCtl1.TxMsg.Data[6] = gSysPar.SB_Rto&0xff;
				gCanBusCtl1.TxMsg.Data[7] =  gSysPar.RB_Mode&0xff;
				gCanBusCtl1.TxMsg.DLC  = 8;
			}
			else if(IDX == 4)
			{
				gCanBusCtl1.TxMsg.Data[0] = gSysPar.RB1_W&0xff;
				gCanBusCtl1.TxMsg.Data[1] = gSysPar.RB1_W>>8;
				gCanBusCtl1.TxMsg.Data[2] = gSysPar.RB1_S&0xff;
				gCanBusCtl1.TxMsg.Data[3] = gSysPar.RB1_L&0xff;
				gCanBusCtl1.TxMsg.Data[4] = gSysPar.RB2_W&0xff;
				gCanBusCtl1.TxMsg.Data[5] = gSysPar.RB2_W>>8;
				gCanBusCtl1.TxMsg.Data[6] = gSysPar.RB2_S&0xff;
				gCanBusCtl1.TxMsg.Data[7] =  gSysPar.RB2_T&0xff;
				gCanBusCtl1.TxMsg.DLC  = 8;
			}
			else if(IDX == 5)
			{
				gCanBusCtl1.TxMsg.Data[0] = gSysPar.LT_Ofs&0xff;
				gCanBusCtl1.TxMsg.Data[1] = gSysPar.LT_Time&0xff;
				gCanBusCtl1.TxMsg.Data[2] = gSysPar.DJ_Ofs_O&0xff;
				gCanBusCtl1.TxMsg.Data[3] = gSysPar.DJ_Time&0xff;
				gCanBusCtl1.TxMsg.Data[4] = gSysPar.YS_Spd&0xff;
				gCanBusCtl1.TxMsg.Data[5] = gSysPar.YS_Spd>>8;
				gCanBusCtl1.TxMsg.Data[6] = gSysPar.YS_Dir&0xff;
				gCanBusCtl1.TxMsg.Data[7] = gSysPar.DJ_Ofs_BC&0xff;
				gCanBusCtl1.TxMsg.DLC  = 8;
			}

			
		}
		// 轮询
		else
		{
				gCanBusCtl1.CurCmd = CAN_CMD_STATUS1;  //轮询单节数据
				gCanBusCtl1.MaxIndex = 0;
				gCanBusCtl1.FinalFrame = 1;
				gCanBusCtl1.RxFlag  = 0;
				gCanBusCtl1.Flg_StsReadMask[gCanBusCtl1.CurNode] = 0;
				IDX = gCanBusCtl1.CurIndex;
				ID = gCanBusCtl1.CurID = gCanBusCtl1.CurNode+1;
				CMD  = gCanBusCtl1.CurCmd;

				gCanBusCtl1.TxMsg.ExtId = (IDX<< 16) + (CMD<<8) + gCanBusCtl1.CurID;
				gCanBusCtl1.TxMsg.Data[0] = gCanBusCtl1.CurID;
				gCanBusCtl1.TxMsg.DLC  = 1;
			
		}


		gCanBusCtl1.State = STS_SEND;

	}
	//发送数据
	else if(gCanBusCtl1.State == STS_SEND)
	{
		can1_buffer_add_msg(&gCanBusCtl1.TxMsg);


		if(gCanBusCtl1.FinalFrame) //最后一帧
		{
			gCanBusCtl1.WaitCnt = 200;// 200ms
			gCanBusCtl1.State = STS_WAIT_OVER_TIME;
		}
		else
		{
			//gCanBusCtl1.WaitCnt = 1;// 1ms
			//gCanBusCtl1.State = STS_WAIT_SEND;
			gCanBusCtl1.CurIndex++;
			gCanBusCtl1.State = STS_LOAD;
		}
	}
	//超时处理
	else if(gCanBusCtl1.State == STS_OVER_TIME)
	{

		//重发
		if(gCanBusCtl1.ReSendCnt> 1)
		{
			gCanBusCtl1.ReSendCnt--;
			if(gCanBusCtl1.FinalFrame == 1)
			{
				gCanBusCtl1.CurIndex = 0;
			}
			gCanBusCtl1.State = STS_LOAD;
		}
		//重发超次数
		else
		{
			if(gCanBusCtl1.ComErrCnt[gCanBusCtl1.CurNode] < 3)
				gCanBusCtl1.ComErrCnt[gCanBusCtl1.CurNode] ++;
			else
				gCanBusCtl1.ComErr[gCanBusCtl1.CurNode] = 1;

			
			
			gCanBusCtl1.CurNode++;
			if(gCanBusCtl1.CurNode >= MAX_NODE_NUM)
			{
				gCanBusCtl1.CurNode = 0;
			}
			gCanBusCtl1.CurIndex = 0;
			gCanBusCtl1.ReSendCnt = MAX_RESEND_NUM;
		

			gCanBusCtl1.State = STS_LOAD;
		}
	}
	// 收到回复
	else if(gCanBusCtl1.State == STS_PARSE)
	{

		gCanBusCtl1.ComErrCnt[gCanBusCtl1.CurNode]=0;
		if(gCanBusCtl1.CurCmd == CAN_CMD_SET_PAR )
		{
			gCanBusCtl1.DataRequestMain[gCanBusCtl1.CurNode] = 0;
		}
		
		gCanBusCtl1.CurNode++;
		if(gCanBusCtl1.CurNode >= MAX_NODE_NUM)
		{
			gCanBusCtl1.CurNode = 0;
		}
		
		gCanBusCtl1.CurIndex = 0;
		gCanBusCtl1.ReSendCnt = MAX_RESEND_NUM;
		gCanBusCtl1.State = STS_LOAD;



	}


	//发送
	pBuf = can1_buffer_get_msg();
	if(pBuf)
	{
		can1_send_msg(pBuf);	
	}
	

}


