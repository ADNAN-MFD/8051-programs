sfr LCD_PORT=0x80;
sbit RS=P3^4;
sbit RW=P3^5;
sbit EN=P3^6;
char buf[10];
void lcd_cmd(unsigned char c)
{
	LCD_PORT=c;
	RS=0;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}

void lcd_data(unsigned char d)
{
	LCD_PORT=d;
	RS=1;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}

void  lcd_init(void)
{
	lcd_cmd(0x2);
	lcd_cmd(0x38);
	lcd_cmd(0x6);
	lcd_cmd(0xE);
	lcd_cmd(0x1);
}

void lcd_string(char *s)
{
	while(*s)
	lcd_data(*s++);
	
}

void lcd_integer(int n)
{
	
	sprintf(buf,"%d",n);
	lcd_string(buf);
}

void lcd_float(float n)
{
	
	sprintf(buf,"%.1f",n);
	lcd_string(buf);
}

void lcd_hex(unsigned char n)
{
	unsigned char i;
	lcd_string("0X");
	i=n/16;
	if(i>9)
		lcd_data(i+55);
	else
		lcd_data(i+48);
	i=n%16;
	if(i>9)
		lcd_data(i+55);
	else
		lcd_data(i+48);
}

void lcd_bin(unsigned char n)
{
	char i;
  for(i=7;i>=0;i--)
		lcd_data(((n>>i)&1)+48);
}
