sbit clk=P1^0;
sbit din=P1^1;
sbit dout=P1^2;
sbit cs=P1^3;


unsigned int adc_read(unsigned char ch)
{
	unsigned int temp=0;
	char i;
	cs=0;
	clk=0;din=1;clk=1;//start
	clk=0;din=1;clk=1;//single ended
	
	clk=0;din=1;clk=1;//d2
	clk=0;din=(ch>>1);clk=1;//d1
	clk=0;din=ch&1;clk=1;//d0
	
	clk=0;din=1;clk=1; //t sample 
	clk=0;din=1;clk=1; //nullbit 
	
	for(i=11;i>=0;i--)
	{
		clk=0;
		if(dout==1)
			temp |=(1<<i);
		clk=1;
	}
	cs=1;
	return temp;
}
