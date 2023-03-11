/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#include "display.h"
#include "duoji.h"
#pragma section all "cpu0_dsram"

//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��





int core0_main(void)
{


	get_clk();//��ȡʱ��Ƶ��  ��ر���

	//Ŀǰ�Ŀ�ɼ������ ͼ�����һ��Ϊ�̶��ĺ�ɫ
	//�������ڵ�Ƭ����ɵģ���������ͷ������



	//�����Ļһֱ��ʾ��ʼ����Ϣ����������ͷ����
    //���ʹ�����壬һֱ����while(!uart_receive_flag)�������Ƿ�������OK?��������ͷ�����ô����뵥Ƭ�������Ƿ���ȷ
    //���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?

    //�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();


	Duoji_Init();
	Duoji_Data_Init();
    lcd_init();
	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    mt9v03x_init();
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);


    Image_Parameter_setting();           //������ʼ��
    //��ʼ������ͷ

	//ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
	while (TRUE)
	{
		if(mt9v03x_finish_flag)
    	{

		    Get_Use_Image();  //�ɼ�ԭʼͼ����ѹ��
		    Get_Bin_Image(0);
		    Bin_Image_Filter();
    		mt9v03x_finish_flag = 0;//��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
			//ע�⣺һ��Ҫ��ͼ��ʹ����Ϻ�������˱�־λ
    	}


		lcd_displayimage032(Bin_Image[0],IMAGEW/2,IMAGEH/2);

		//shang_wei_ji(UART_0,Bin_Image[0],IMAGEW/2,IMAGEH);
      seekfree_sendimg_03x(UART_0, Bin_Image[0], IMAGEW/2, IMAGEH);

	}
}

#pragma section all restore


