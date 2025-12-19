#include<LPC21xx.h>
#include"LCD.h"
#define lCD_d 0xff
#define SW 14
#define SW1 15
int count =0;

unsigned char cg_lut[] = {0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x00,
			0x00,0x0A,0x00,0x04,0x00,0x0A,0x00,0x00,
			0x00,0x0A,0x00,0x00,0x00,0x0A,0x00,0x00,
			0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x00,
			0x00,0x00,0x08,0x00,0x00,0x02,0x00,0x00,
			0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00
			};


void cg_write(int n)
{
	unsigned char i;
	n=n*8;
	LCD_CMD(0x40);
	for(i=0;i<n;i++)
	{
	LCD_DATA(cg_lut[i]);
	}
	T1PR = 5;
	T1TCR =0x01;
}
int random()
{
	return T1PC;
}

int main()
{		
		unsigned char p1[]={0,0,0,0,0},p2[]={0,0,0,0,0},flag=0,val,i1=0,i2=0;			 
	 	LCD_INIT();
		cg_write(6);
		LCD_CMD(0X80);
		LCD_STRING("DIGITAL DICE");
	
		while(1)
		{
			int i;
			if(((IOPIN0>>SW)&1)==0)
			{
				for(i=0;i<6;i++)
				{
					LCD_CMD(0XC0);
					LCD_DATA(i);
					DELAY(50);
				}
				val = random();
				LCD_CMD(0XC0);
				LCD_DATA(val);
				switch(val+1)
				{
				case 1:
					val = 6;break;
				case 2:
					val = 5;break;
				case 3:
					val = 4;break;
				case 4: 
					val = 3;break;
				case 5:
					val = 2;break;
				case 6:
					val = 1;break;
				}
				if(flag == 0)
				{
					if(i1>=5)
					{
						for(i=0;i<=3;i++)
						{
							p1[i] = p1[i+1];
						}
						p1[i]=val;
					}
					else
					{
					p1[i1++] = val;
					}
					flag=1;
				}
				else if(flag==1)
				{
				 	if(i2>=5)
					{
						for(i=0;i<=3;i++)
						{
							p2[i] = p2[i+1];
						}
						p2[i]=val;
					}
					else
					{
					p2[i2++] = val;
					}
					flag=0;
				}				
				while(((IOPIN0>>SW)&1)==0);
			}
			if(((IOPIN0>>SW1)&1)==0)
			{
				LCD_CMD(0X01);
				LCD_CMD(0X80);
				LCD_STRING("P1:");
				for(i=0;i<=4;i++)
				{
					LCD_DATA(p1[i]+48);
				}
				LCD_CMD(0Xc0);
				LCD_STRING("P2:");
				for(i=0;i<=4;i++)
				{
					LCD_DATA(p2[i]+48);
				}
				while(((IOPIN0>>SW1)&1)==0);
				LCD_CMD(0x01);
				LCD_CMD(0X80);
				LCD_STRING("DIGITAL DICE");

			}
		}
	
}

