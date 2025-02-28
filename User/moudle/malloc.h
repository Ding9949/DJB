#ifndef __MALLOC_H
#define __MALLOC_H

#include "stm32f4xx.h"
#include "sys_define.h"



//mem1内存参数设定.mem1完全处于内部SRAM里面
#define MEM1_BLOCK_SIZE			32  	  						//内存块大小为32字节
#if SRAM_TYPE == SRAMIN
#define MEM1_MAX_SIZE			1*1024   						//最大管理内存 45K
#else
#define MEM1_MAX_SIZE			32  						//最大管理内存 45K
#endif
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//内存表大小

//mem2内存参数设定.mem2的内存池处于外部SRAM里面,其他的处于内部SRAM里面
#define MEM2_BLOCK_SIZE			32  	  						//内存块大小为32字节
#if SRAM_TYPE == SRAMEX
#define MEM2_MAX_SIZE			128*1024  						//最大管理内存 256K
#else
#define MEM2_MAX_SIZE			32  						//最大管理内存 128K
#endif
#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	//内存表大小
		 
#if 0
//内存管理控制器
struct _m_mallco_dev
{
	void (*init)(u8);					//初始化
	u8 (*perused)(u8);		  	    	//内存使用率
	u8 	*membase[2];					//内存池 管理2个区域的内存
	u16 *memmap[2]; 					//内存管理状态表
	u8  memrdy[2]; 						//内存管理是否就绪
};
#else
typedef struct _malloc_dev_s
{
	void (*init)(u8);					//初始化
	u8 (*perused)(u8);		  	    	//内存使用率
	u8 	*membase[2];					//内存池 管理2个区域的内存
	u16 *memmap[2]; 					//内存管理状态表
	u8  memrdy[2]; 						//内存管理是否就绪
}malloc_dev_t;
#endif
//extern struct _m_mallco_dev mallco_dev;	 //在mallco.c里面定义

void mymemset(void *s,u8 c,u32 count);	 //设置内存
void mymemcpy(void *des,void *src,u32 n);//复制内存 

void mem_init(u8 memx);					 //内存管理初始化函数(外/内部调用)
u32 mem_malloc(u8 memx,u32 size);		 //内存分配(内部调用)
u8 mem_free(u8 memx,u32 offset);		 //内存释放(内部调用)
u8 mem_perused(u8 memx);				 //获得内存使用率(外/内部调用) 
////////////////////////////////////////////////////////////////////////////////
//用户调用函数
void myfree(u8 memx,void *ptr);  			//内存释放(外部调用)
void *mymalloc(u8 memx,u32 size);			//内存分配(外部调用)
void *myrealloc(u8 memx,void *ptr,u32 size);//重新分配内存(外部调用)
#endif













