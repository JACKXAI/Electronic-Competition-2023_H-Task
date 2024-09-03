#include "SysTick.h"
#include "sys.h"
#include "usart.h"

#include "fft_calculate.h"
#include "adc.h"
#include "time.h"
#include "AD9834.h" 
//#include "oledfont.h"  
#include "oled.h"

u32 Freq;
u8 freq_A_str[16];
u8 freq_B_str[16];
u16 Row;
u16 Max_Val=0;
u16 adc_value[5];
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	u16 i;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组

	USART1_Init(9600);

	TIM1_Init();
	ADC1_DMA1_Init();
	ADC1_Init();
	TIM_Cmd(TIM1, ENABLE);

	OLED_Init();			//初始化OLED  
	OLED_Clear()  	; 	
	
	AD9834_Init();
	while(1)
	{
		//Max_Val=0;
		for(i=2;i<NPT/2;i++)
		{
			if(MagBufArray[i]>Max_Val)
			{
				Max_Val=MagBufArray[i];
				Row=i;
			}
		}
		Freq=(72000000)/(NPT*(ARR+1)*(PSC+1)/Row);
    // 输出和显示频率A
    sprintf(freq_A_str, "Freq A: %lu Hz", Freq);
		printf(freq_A_str);
    OLED_ShowString(0, 0, "hello");

    // 输出和显示频率B
    sprintf(freq_B_str, "Freq B: %lu Hz", Freq);
		printf(freq_A_str);
    OLED_ShowString(0, 2, freq_B_str);
		
		AD9834_Select_Wave(Sine_Wave);//Sine_Wave  Square_Wave  Triangle_Wave
		AD9834_Set_Freq(FREQ_1, Freq);		
	  delay_ms(100);
	}
}