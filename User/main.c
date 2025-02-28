/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sys_include.h"



void app_pre_init(void)
{
	//do something witch will be excue in startup before main function
}
//u8 * data = NULL;
//u8 * data1 = NULL;

//u8 k[1000] = {0,};
//	u16 i = 0;
int main(void)
{
	#ifdef USE_IAP
	nvic_vector_table_set(FLASH_BASE, FLASH_BOOT_SIZE);
	#else
	nvic_vector_table_set(FLASH_BASE, 0);
	#endif
	delay_init(120);
	nvic_init();

	#ifdef USE_IAP
	iap_get_mark();	
	IapMarkInfo.AppVer = CODE_VER;
	IapMarkInfo.IapMarkWord = 0;	
	iap_save_mark();
	#endif

	

	main_task();

}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif
