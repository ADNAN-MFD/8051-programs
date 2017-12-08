void i2c_device_write(unsigned char addr, unsigned char mry ,unsigned char _data)
{
	i2c_start();
	i2c_write(addr);
	i2c_ack();
	i2c_write(mry);
	i2c_ack();
	i2c_write(_data);
	i2c_ack();
	i2c_stop();
	delay_ms(10);
}

unsigned char i2c_device_read(unsigned char addr,unsigned char mry)
{
	unsigned char _data;
	i2c_start();
	i2c_write(addr);
	i2c_ack();
	i2c_write(mry);
	i2c_ack();
	i2c_start();
	i2c_write(addr|1);
	i2c_ack();
	_data=i2c_read();
	i2c_nack();
	i2c_stop();
	delay_ms(10);
	return _data;
}
	
unsigned char i2c_detect(unsigned char addr)
{
	unsigned char flag;
	
	i2c_start();
	i2c_write(addr);
	flag=i2c_cack();
	i2c_stop();
	delay_ms(10);
	return flag;
}
//multiple memory write frame
void i2c_device_mwrite(unsigned char addr, unsigned char mry ,unsigned char *_data,unsigned char n)
{
	unsigned char i;
	i2c_start();
	i2c_write(addr);
	i2c_ack();
	i2c_write(mry);
	i2c_ack();
	for(i=0;i<n;i++)
	{
	i2c_write(_data[i]);
	i2c_ack();
	}
	i2c_stop();
	delay_ms(10);
}

//multiple memory read frame based on datasheet of ds1307
void i2c_device_mread(unsigned char addr,unsigned char mry,unsigned char *_data,unsigned char n)
{
	char i=0;
	i2c_start();
	i2c_write(addr);
	i2c_ack();
	i2c_write(mry);
	i2c_ack();
	i2c_start();
	i2c_write(addr|1);
	i2c_ack();
	_data[i]=i2c_read();
	for(i=1;i<n;i++)
	{
		i2c_dack();
	_data[i]=i2c_read();
	}
	i2c_nack();
	i2c_stop();
	delay_ms(10);
}
