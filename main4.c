#include <reg51.h>
#include <stdio.h>
#include "delay_ms.h"
#include "lcd8bit.h"
#include "i2c.h"
#include "i2c_device.h"

code char day[7][5]={" Sun"," Mon"," Tue"," Wed"," Thu"," Fri"," Sat"};

void main()
{
	unsigned char temp,m;
	lcd_init();
	lcd_cmd(0x0c);
	i2c_device_write(0xd0,0x02,0x11|0x60);//setting hr to 12hr format also setting hr value 11 pm
	i2c_device_write(0xd0,0x01,0x59);     //setting mins 59
	i2c_device_write(0xd0,0x00,0x50);     //setting seconds 50
	//setting date to 31/12/16
	i2c_device_write(0xd0,0x04,0x31);  
	i2c_device_write(0xd0,0x05,0x12);
	i2c_device_write(0xd0,0x06,0x16);
	//start reading values
	while(1)
	{
	lcd_cmd(0x80);
	temp=i2c_device_read(0xd0,0x02);
  if(temp & 0x20)	 // check for am or pm
	  m=1;
	else
		m=0;
	temp &=0x1f;    //first 5 bits contains hr value
	lcd_data(temp/16+48);
	lcd_data(temp%16+48);
	
	lcd_data(':');
	
	temp=i2c_device_read(0xd0,0x01);
	lcd_data(temp/16+48);
	lcd_data(temp%16+48);
	
	lcd_data(':');
	
	temp=i2c_device_read(0xd0,0x00);
	lcd_data(temp/16+48);
	lcd_data(temp%16+48);
	
	if(m==1)        // prints am or pm
		lcd_string(" pm");
	else
		lcd_string(" am");
	
	lcd_cmd(0xc0);
	
	temp=i2c_device_read(0xd0,0x04);
	lcd_data(temp/16+48);
	lcd_data(temp%16+48);
	
	lcd_data('/');
	
	temp=i2c_device_read(0xd0,0x05);
	lcd_data(temp/16+48);
	lcd_data(temp%16+48);
	
	lcd_data('/');
	
	temp=i2c_device_read(0xd0,0x06);
	lcd_data(temp/16+48);
	lcd_data(temp%16+48);
   
	lcd_data(' ');
	temp=i2c_device_read(0xd0,0x03);
	lcd_string(day[temp-1]);          //selects the day and printing on lcd

}
	
}