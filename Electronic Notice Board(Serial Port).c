#include<stdio.h>
#include<at89c51xd2.h>

void lcd_comm(void); 
void delay(int);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_init2(void);
unsigned char temp1;
unsigned char temp2;
unsigned char var,j;
sbit RS = P2^7;
sbit EN = P2^6;
sbit RW = P2^5;		   
unsigned char x;
unsigned char i=0;
   
int main()
{	
lcd_init();

SCON = 0x50;
TMOD = 0x20;
TH1 = 0xfd;
TR1 = 1;

while(1)
	{
	while(RI==0);
	x=SBUF;
	RI=0;
	SBUF=x;
	while(TI==0);
	TI=0;
	lcd_data(x);
	delay(65000);
	if(i==16)
	lcd_init2();
	}
}
  
void lcd_init(void)
{
unsigned int cmd[]={0x20,0x28,0X06,0X0E,0X0E,0X80};
unsigned int j;
for(j=0;j<6;j++)
	{
	temp1=cmd[j];
	lcd_comm();
    delay(1000);
	}
}

void lcd_init2(void)
{
unsigned int cmd[]={0x20,0x28,0X06,0X0E,0X0E,0Xc0};
unsigned int j;
for(j=0;j<6;j++)
	{
	temp1=cmd[j];
	lcd_comm();
    delay(1000);
	}
 }

void lcd_comm(void) 
{
	var = temp1; 
  	temp1 = temp1 & 0xf0; 
  	temp1 = temp1 >> 4;		
	P2 = temp1;
    RS=0;							   
    EN=1;   
	delay(10);
    EN=0;	
  	temp1 = var & 0x0f;		
	P2 = temp1;
    RS=0;							 
    EN=1;   
	delay(10);
    EN=0;
}

void lcd_data(unsigned char temp2)
{
   	var = temp2; 
  	temp2 = temp2 & 0xf0;  
  	temp2 = temp2 >> 4;   
  	P2 = temp2;
	RS=1;		 
	EN=1;
	delay(10);
	EN=0;
  	temp2 = var & 0x0f;	   
	P2 = temp2;
	RS=1;		 
	EN=1;
	delay(10);
	EN=0;
   	delay(5000);
	i++;
}  

void delay(int count)
{
	int i;
   	for(i=0;i<count;i++);
}
