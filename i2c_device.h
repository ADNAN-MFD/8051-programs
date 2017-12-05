
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
}