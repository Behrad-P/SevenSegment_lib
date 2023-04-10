# SevenSegment_lib
Seven segment driver for STM32 and AVR Microcontroller

I use Stm32f103c8 and Keil Compiler and Stm32CubeMX wizard.
Please Do This ...

1) Select "General peripheral Initalizion as a pair of '.c/.h' file per peripheral" on project settings.
2) Config your LCD Pins on CubeMX.
3) Config your LCD pins on "LCD_Config.h".
4) Call LCD_Init() and Enjoy!!

```
#include "LCD.h"
.
.
.
int main()
{
  .
  .
  LCD_Init(); 
  LCD_Puts(0,0,"TEST");
  .
  .
}


```
