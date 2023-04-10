

/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     CodeVisionAVR
 * @brief   SevenSegment driver library (.c) 
*/

#include <sevensegment.h>
#include <delay.h>


#define negative            0x01
#define positive            0x02

#define set_pin(Pin)        (Pin = 1)
#define clear_pin(Pin)      (Pin = 0)

#define stcp_C_blink        set_pin(stcp_C_pin); delay_us(200); clear_pin(stcp_C_pin);  
#define stcp_D_blink        set_pin(stcp_D_pin); delay_us(200); clear_pin(stcp_D_pin);
#define stcp_cap            stcp_C_blink; stcp_D_blink;

static void Err(void);
static void ShowNumber(char D, char C);
static void SPI_Write(char data);
static char NumberOverFlowCheck(float Number);       

typedef struct{

    unsigned char Protocol;
    unsigned char Digits;
    unsigned char LED_Type; 
    unsigned int Blink_Period;
    unsigned char Blink_Flag;
    
}SevenSegmentOptions_t; 

SevenSegmentOptions_t SevenSegment;

typedef struct{

	float         Fractional_Part;
	unsigned int  Integral_Part;
	unsigned int  Counter;
	unsigned int  Data;
    unsigned int  ControlData;
    unsigned char OverFlowFlag;

}SevenSegmentVariables_t;

SevenSegmentVariables_t SevenSegment_Var;


static const unsigned char BCD_to_7Segment[11]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40};
static const unsigned char OFL[3]={0x3F,0x71,0x38};
static const unsigned char BCD_OFL[3]={10,0,11};

void SevenSegment_Write(float Number)
{
char i=0;
static unsigned int IPart, FPart, Counter;
static signed char Digit, ZeroShow, NumberSign, Toggle_Flag;

	SevenSegment_Var.OverFlowFlag = NumberOverFlowCheck(Number);
    
    if(SevenSegment_Var.OverFlowFlag == 1)
        Err();
    else
    {
        if(Digit == 0)
        {
            if(Number < 0)
            {
            	NumberSign = negative;
                Number*= -1.0;
            }
            else
            	NumberSign = positive;
                       
            SevenSegment_Var.Integral_Part = Number / 1;
            SevenSegment_Var.Fractional_Part = (((Number - SevenSegment_Var.Integral_Part) * 10.0) / 1);
            ZeroShow = 0;
            
            if(NumberSign == negative)
            {
                if(SevenSegment.Protocol != bcd)
                	SevenSegment_Var.Data = 10;
            }
            else
            {
                i = SevenSegment.Digits - 2;   
                while(i)
                { 
                	IPart/= 10;
                    i--;
                }
                SevenSegment_Var.Data = IPart;
                if(SevenSegment_Var.Data != 0)
                    ZeroShow = 1;
            }          
        } 
        else if(Digit > 0 && Digit <= SevenSegment.Digits - 3) 
        {
            for(i = SevenSegment.Digits - 3 ; i >= Digit ; i--)
            	IPart/= 10;
            
            SevenSegment_Var.Data = IPart % 10;
            if(SevenSegment_Var.Data != 0)
                ZeroShow = 1;      
        } 
        
        else if(Digit == SevenSegment.Digits - 1) SevenSegment_Var.Data = FPart%10;
        if(Digit == SevenSegment.Digits - 2) SevenSegment_Var.Data = IPart%10;
        
        
        if(SevenSegment_Var.Data != 0 || ZeroShow == 1 || Digit >= SevenSegment.Digits - 2)
        {   
            if(SevenSegment.Protocol != bcd)
            {
            	SevenSegment_Var.Data = BCD_to_7Segment[SevenSegment_Var.Data];
                if(Digit == SevenSegment.Digits - 2)
                	SevenSegment_Var.Data = 1 << 7 | SevenSegment_Var.Data;
            } 
            else
            {
                if(Digit == SevenSegment.Digits - 2)
                	SevenSegment_Var.Data = 1 << 4 | SevenSegment_Var.Data;
            }  
                      
            SevenSegment_Var.ControlData = 1 << Digit;
        }
        else
        {
        	SevenSegment_Var.ControlData = 0;
        	SevenSegment_Var.Data = 0;
        }
                 
        Digit++;
        if(Digit > SevenSegment.Digits - 1)
            Digit = 0;
        
        if(SevenSegment.Blink_Flag == 1)
        {
            Counter++;
            if(SevenSegment.Blink_Period == Counter)
            {
                Toggle_Flag^= 1;
                Counter = 0;
            }
        }   
        else
        {
            Counter = 0;
            Toggle_Flag = 0;
        }
            
        if(Toggle_Flag == 1)
        {
        	SevenSegment_Var.ControlData = 0;
        	SevenSegment_Var.Data = 0;
        }
        
        IPart = SevenSegment_Var.Integral_Part;
        FPart = SevenSegment_Var.Fractional_Part;
        if(SevenSegment.Protocol == bcd && NumberSign == negative)
            Err();
        else    
            ShowNumber(SevenSegment_Var.Data, SevenSegment_Var.ControlData);
    }       
}

static void Err(void)
{
static unsigned char Digit;

    SevenSegment_Var.ControlData = 1 << Digit;
    if(SevenSegment.Protocol != bcd) 
        SevenSegment_Var.Data = OFL[Digit];
    else
        SevenSegment_Var.Data = BCD_OFL[Digit];
       
    Digit++;
    if(Digit > 2)
        Digit=0;
            
    ShowNumber(SevenSegment_Var.Data, SevenSegment_Var.ControlData);
}

static void ShowNumber(char D, char C)
{
    if(SevenSegment.LED_Type == ca)
    {
        D = ~D;
        C = ~C;
    }
    
    if(SevenSegment.Protocol != spi)
    {
        control_port = C;
        delay_us(200);
        data_port = D;    
        delay_us(200);
    }
    else
    {
        SPI_Write(C);
        SPI_Write(D);
        stcp_cap;
    }       
}

void SevenSegment_Init(unsigned char Protocol, unsigned char Digits, unsigned char LED_Type)                   
{
    SevenSegment.Digits = Digits; 
    SevenSegment.Protocol = Protocol;
    SevenSegment.LED_Type = LED_Type;
}

void SevenSegment_SPI_Init(void)                   
{  
    DDRB = 0xBF;    
    PORTB = 0x00;          
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);    
    SPSR &= ~(1<<SPI2X);            
}

static void SPI_Write(unsigned char data)        
{
    SPDR = data;            
    while(!(SPSR & (1<<SPIF)));   
    SPSR &= ~(1<<SPIF);             
}

static char NumberOverFlowCheck(float Number)
{
static unsigned char Counter = 0;
static char Of_Flag = 1;

    Counter++;
    if(Counter > 200)
    {
        switch(SevenSegment.Digits) 
        {
            case 8:
            if(Number > 65500.0 || Number < -65500.0)
                Of_Flag = 1;
            else
                Of_Flag = 0;
            break;
        
            case 7:
            if(Number > 65500.0 || Number < -65500.0)
                Of_Flag = 1;
            else
                Of_Flag = 0;
            break;
        
            case 6:
            if(Number > 65500.0 || Number < -9999.9)
                Of_Flag = 1;
            else
                Of_Flag = 0;
            break;
        
            case 5:
            if(Number > 9999.9 || Number < -999.9)
                Of_Flag = 1;
            else
                Of_Flag = 0;
            break;
        
            case 4:
            if(Number > 999.9 || Number < -99.9)
                Of_Flag = 1;
            else
                Of_Flag = 0;
            break;
        
            case 3:
            if(Number > 99.9 || Number < -9.9)
                Of_Flag = 1;
            else
                Of_Flag = 0;
            break;
        
            case 2:
            if(Number > 9.9 || Number < 0)
                Of_Flag = 1;
            else
                Of_Flag = 0;
            break;
        
            default:
                Of_Flag = 1;
	    break; 
        }
        Counter = 0;
    }
    return Of_Flag;   
}

void SevenSegment_Blink_On(unsigned int Blink_Delay)
{
    SevenSegment.Blink_Flag = 1;  
    SevenSegment.Blink_Period = Blink_Delay; 
}

void SevenSegment_Blink_Off(void)
{
    SevenSegment.Blink_Flag = 0;
} 


