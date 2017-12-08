sbit sda= P2^0;
sbit scl=P2^1;

void i2c_start() //while clock is high, A high to low transition in SDA is count as start condition 
{
	scl=1; 
	sda=1;
	sda=0;
}

void i2c_stop()//After one clock pulse(low to high), a low to high transition in SDA count as stop condition
{
	scl=0;//SCL line is low
	sda=0;//SDA line is high
	scl=1;//SCl line is high(one clock pulse)
	sda=1;//SDA low to high transition
}

void i2c_write(unsigned char _data)
{
	char i;
	for(i=7;i>=0;i--)
	{
		scl=0;        
		sda=(_data&(1<<i))?1:0;//while SCL is low data transition(data change) take place
		scl=1;//data sampling take place(slave will read SDA line)
	}
}

unsigned char i2c_read()
{
	unsigned char temp=0;
	char i;
	for(i=7;i>=0;i--)
	{
		scl=1;
		if(sda)//scl is high master read the sda line
		 temp |=1<<i;
		scl=0;//data transtion take place by slave
	}
	return temp;
}

void i2c_ack()//acknowledge from master to slave
{
	scl=0;
	sda=1;//master make sda high
	scl=1; //master make scl high ie. one clock pulse and release sda line
	while(sda==1);//wait untill slave to put high on sda
	scl=0; //master will clear scl for further action
}
void i2c_dack() //acknowledge from slave to master
{
	scl=0;
  while(sda==0);//wait untill slave put high on sda line and releases sda
	sda=0; //master clear sda line
	scl=1;//give a clock pulse
	scl=0;//master clears clock line
	sda=1;//master make sda high and releases sda
}

void i2c_nack()
{
	scl=0;
	sda=1;//master will make SDA high and in nonack master will not wait for slave response
	scl=1;
}

unsigned char i2c_cack()//same as i2c_ack but it is not a blocking function if slave will not respond then function will exit
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
