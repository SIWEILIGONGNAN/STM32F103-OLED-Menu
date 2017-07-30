#include "key.h"
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "menu.h"

extern int Level,Menu_Page;
extern int sum;

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	 
 	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOC, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
 	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void LED_Reverse(void)
{
	LED=~LED;
}

int KEY_Scan(void)
{
	if ((!KEY1) || (!KEY2) || (!KEY3) || (!KEY4))
	{
		delay_ms(80);
		if (!KEY1)
			return 1;
		else if (!KEY2)
			return 2;
		else if (!KEY3)
			return 3;
		else if (!KEY4)
			return 4;
		else
			return 0;
	}
	return 0;
}

void KEY_Func(int KEY)
{
	switch (KEY)
	{
		case 1:											//����
		{
			if (Level==0)
			{
				Level=MAX_LEVEL;
				if (Menu_Page==1)
				{
					Menu_Page=MAX_PAGE;
					Menu_Display(Menu_Page,Level);
				}
				else 
				{
					Menu_Page--;
					Menu_Display(Menu_Page,Level);
				}
			}
			else 
			{
				Level-=2;
				Menu_Display(Menu_Page,Level);
			}
			break;
		}
		case 2:											//����
		{
			if (Level==MAX_LEVEL)
			{
				Level=0;
				if (Menu_Page==MAX_PAGE)
				{
					Menu_Page=1;
					Menu_Display(Menu_Page,Level);
				}
				else
				{
					Menu_Page++;
					Menu_Display(Menu_Page,Level);
				}
			}
			else
			{
				Level+=2;
				Menu_Display(Menu_Page,Level);
			}
			break;
		}
		case 3:											//ȷ��
		{
			sum=Menu_Page*10 + Level;				
			switch(sum)
			{
				case 10:
				{
					/***************************************
					�ڴ����ѡ��Ĺ��ܣ�����ʾ������Ϊʾ��
					***************************************/
					OLED_Clear();
					OLED_ShowString(0,0,"Sun Yang");
					break;
				}
				case 12:
				{
					OLED_Clear();
					OLED_ShowString(0,0,"Xu Jingxin");
					break;
				}
				case 14:
				{
					OLED_Clear();
					OLED_ShowString(0,0,"Feng Dayong");
					break;
				}
				case 16:{break;}
				
				case 20:{break;}
				case 22:{break;}
				case 24:{break;}
				case 26:{break;}
				
				case 30:{break;}
				case 32:{break;}
				case 34:{break;}
				case 36:
				{
					OLED_Clear();
					OLED_ShowString(0,0,"Zhang Yuxiao");
					break;
				}
				/*****************************
					�������ҳ�棬�ڴ����
				*****************************/
				default: break;
			}
			break;
		}
		case 4:											//ȡ��
		{
			Menu_Display(Menu_Page,Level);
		}
		break;
		default: break;
	}
}
