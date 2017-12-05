#include <reg51.h>
#include"delay_ms.h"
#include"lcd8bit.h"
code char name[5]="amal";
void main()
{
	unsigned char i,j;
	lcd_init();
	lcd_cmd(0x0c);//lcd cursor off
	while(1)
	{
			j=4;//length of the string to scroll
	for(i=0;i<16;i++)
	{
		lcd_cmd(0x01);//clear lcd screen
		if((i+j+1)>16)  //To check whether name exceeds first line
		{
		   lcd_cmd(0x80);
			 lcd_string(name+j);
			j--;
		}
		lcd_cmd(0x80+i);		
		lcd_string(name);
		delay_ms(1000);
	}
  }
}
