/*DS1307 RTC interfacing with AT89c51 using i2c Protocol(Bit Banging Method)
*********************Clock with time and date*********************
*********************Multiple memmory read and write ***********************
*/
#include <reg51.h>
#include <stdio.h>
#include "delay_ms.h"
#include "lcd8bit.h"
#include "i2c.h"
#include "i2c_device.h"
void lcd_bcd(unsigned char);

code char day[7][5]={" Sun"," Mon"," Tue"," Wed"," Thu"," Fri"," Sat"};

void main()
{
	unsigned char temp,m,_data[8]={0x50,0x59,0x11|0x60,0x01,0x31,0x12,0x16};
	lcd_init();
	lcd_cmd(0x0c);
	i2c_device_mwrite(0xd0,0x00,_data,7);//writes array values to memory address starting from 0x00
	//start reading values
	while(1)
	{
	lcd_cmd(0x80);
	i2c_device_mread(0xd0,0,_data,7);//reads the 7 bytes of data from mry address 0x00
  if(_data[2]& 0x20)	 // check for am or pm
	  m=1;
	else
		m=0;
	_data[2] &=0x1f;    //first 5 bits contains hr value
  lcd_bcd(_data[2]);
	
	lcd_data(':');

	lcd_bcd(_data[1]); //minutes
	
	lcd_data(':');
	
//i2c_device_read(0xd0,0x00);
	lcd_bcd(_data[0]); //seconds
	
	if(m==1)        // prints am or pm
		lcd_string(" pm");
	else
		lcd_string(" am");
	
	lcd_cmd(0xc0);
	
	// prints date in dd/mm/yy format 
	
  lcd_bcd(_data[4]); 
	lcd_data('/');
	
	lcd_bcd(_data[5]);
	lcd_data('/');
	
	lcd_bcd(_data[6]);
   
	lcd_data(' ');
	lcd_string(day[_data[3]-1]);          //selects the day and printing on lcd

}
	
}
void lcd_bcd(unsigned char temp)//prints bcd alues to lcd screen
{
		lcd_data(temp/16+48);
	  lcd_data(temp%16+48);
}