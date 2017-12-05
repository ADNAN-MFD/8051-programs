/*MCP204 interfacing with AT89c51 using spi bus

   ******* Display the voltage values at 3 channels of MCP204*****
	 */

#include <reg51.h>
#include <stdio.h>
#include "delay_ms.h"
#include "lcd8bit.h"
#include "adc.h"

void main()
{
	unsigned int temp;
	float vol;
	lcd_init();
	while(1)
	{

		lcd_cmd(0x01);
		lcd_string("C0=");
		temp=adc_read(0);
		vol=0.02*(float)temp/16.384;
		lcd_float(vol);
		lcd_data('V');

		lcd_cmd(0x88);
		lcd_string("C1=");
		temp=adc_read(1);
		vol=0.02*(float)temp/16.384;
		lcd_float(vol);
		lcd_data('V');

	  lcd_cmd(0xc0);
		lcd_string("C2=");
		temp=adc_read(2);
		vol=0.02*(float)temp/16.384;
		lcd_float(vol);
		lcd_data('V');
		
		delay_ms(500);
	}
}