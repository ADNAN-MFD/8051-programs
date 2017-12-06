/***** Find the slave address of multiple slaves connected on I2c bus connected to 8051*****/

#include <reg51.h>
#include <stdio.h>
#include "delay_ms.h"
#include "lcd8bit.h"
#include "i2c.h"
#include "i2c_device.h"

void main()
{
	unsigned char i,temp,count=0;
	lcd_init();
	lcd_cmd(0x0c);
	for(i=0;i<=254;i+=2)
	{
		lcd_cmd(0x01);
		lcd_string("checking  : ");
		lcd_hex(i);
		temp=i2c_detect(i);
		if(temp)
		{
			lcd_cmd(0xc0);
			lcd_hex(i);
			lcd_string("Found");
			count++;
			delay_ms(1000);
		}
		if(i>=254)
			break;
	}
	lcd_cmd(0xc0);
	lcd_string("Devices : ");
	lcd_integer(count);
  while(1);
}
