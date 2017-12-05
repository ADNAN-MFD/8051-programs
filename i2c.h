sbit sda= P2^0;
sbit scl=P2^1;

void i2c_start()
{
	scl=1;
	sda=1;
	sda=0;
}

void i2c_stop()
{
	scl=0;
	sda=0;
	scl=1;
	sda=1;
}

void i2c_write(unsigned char _data)
{
	char i;
	for(i=7;i>=0;i--)
	{
		scl=0;
		sda=(_data&(1<<i))?1:0;
		scl=1;
	}
}

unsigned char i2c_read()
{
	unsigned char temp=0;
	char i;
	for(i=7;i>=0;i--)
	{
		scl=1;
		if(sda)
		 temp |=1<<i;
		scl=0;
	}
	return temp;
}

void i2c_ack()
{
	scl=0;
	sda=1;
	scl=1;
	while(sda==1);
	scl=0;
}

void i2c_nack()
{
	scl=0;
	sda=1;
	scl=1;
}

unsigned char i2c_cack()
{
	unsigned char flag=1;
	scl=0;
	sda=1;
	scl=1;
	if(sda==1)
	{
		delay_ms(100);
		if(sda==1)
			flag=0;
	}
	return flag;
}
	
