# Seven segment driver for STM32 and AVR Microcontroller

I tested this library on atmega32 and stm32f103r6 microcontrollers.

3 types of connections between micro and sevensegments are included in this library.

__1. BCD__

code:

```
#include <mega32.h>
#include <delay.h>
#include <sevensegment.h>

float n = 100.5;

void main(void)
{

DDRC = 0xFF;
DDRD = 0xFF;

SevenSegment_Init(bcd, 6, cc);

while (1)             
    {
        SevenSegment_Write(n);
        delay_ms(4);
    }
}

```
![Uploading sevendegment_BCD.png…]()


__2. SPI__

code:

```

#include <mega32.h>
#include <delay.h>
#include <sevensegment.h>

float n = -1120.5;

void main(void)
{

DDRA = 0x03;
SevenSegment_Init(spi, 6, cc);
SevenSegment_SPI_Init();

while (1)             
    {
        SevenSegment_Write(n);
        delay_ms(4);
    }
}

```
![Uploading sevendegment_SPI.png…]()


__3. DIRECT__

code:

```

#include <mega32.h>
#include <delay.h>
#include <sevensegment.h>

float n = 53.2;

void main(void)
{

DDRC = 0xFF;

DDRD = 0xFF;
SevenSegment_Init(direct, 4, ca);

while (1)             
    {
        SevenSegment_Write(n);
        delay_ms(4);
    }
}
```
![Uploading sevendegment_DIRECT.png…]()

**Note:** 
All connections and functions are the same in stm32f103r6 microcontroller




