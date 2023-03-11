/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#include "display.h"
#include "duoji.h"
#pragma section all "cpu0_dsram"

//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中





int core0_main(void)
{


	get_clk();//获取时钟频率  务必保留

	//目前的库采集总钻风 图像最后一列为固定的黑色
	//这是由于单片机造成的，不是摄像头的问题



	//如果屏幕一直显示初始化信息，请检查摄像头接线
    //如果使用主板，一直卡在while(!uart_receive_flag)，请检查是否电池连接OK?或者摄像头的配置串口与单片机连接是否正确
    //如果图像只采集一次，请检查场信号(VSY)是否连接OK?

    //等待所有核心初始化完毕
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();


	Duoji_Init();
	Duoji_Data_Init();
    lcd_init();
	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    mt9v03x_init();
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);


    Image_Parameter_setting();           //参数初始化
    //初始化摄像头

	//注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
	while (TRUE)
	{
		if(mt9v03x_finish_flag)
    	{

		    Get_Use_Image();  //采集原始图像并且压缩
		    Get_Bin_Image(0);
		    Bin_Image_Filter();
    		mt9v03x_finish_flag = 0;//在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像
			//注意：一定要在图像使用完毕后在清除此标志位
    	}


		lcd_displayimage032(Bin_Image[0],IMAGEW/2,IMAGEH/2);

		//shang_wei_ji(UART_0,Bin_Image[0],IMAGEW/2,IMAGEH);
      seekfree_sendimg_03x(UART_0, Bin_Image[0], IMAGEW/2, IMAGEH);

	}
}

#pragma section all restore


