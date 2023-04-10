# SevenSegment_lib
Seven segment driver for STM32 and AVR Microcontroller

 __Example: (AVR) Microcontroller__

I use Atmega32 in this example

1) in direct mode:

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
