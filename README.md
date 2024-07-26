# SevenSegment Driver Library for STM32 and AVR Microcontrollers

This library provides a robust and flexible driver for seven-segment displays, compatible with STM32 and AVR microcontrollers. It has been tested on the ATmega32 and STM32F103R6 microcontrollers.

## Features

- Supports multiple types of connections between microcontrollers and seven-segment displays.
- Easy integration with existing projects.
- Well-documented and organized code for easy customization and extension.

## Supported Microcontrollers

- ATmega32
- STM32F103R6

## Connection Types

This library includes support for three types of connections between the microcontroller and the seven-segment display:

1. Direct connection
2. SPI
3. Shift register-based connection (BCD)


## 1. BCD

__example:__

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

![sevendegment_BCD](https://user-images.githubusercontent.com/129272853/230951598-46248a43-f659-4e6e-9e25-ee010a56fc9b.png)


## 2. SPI

__example:__

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

![sevendegment_SPI](https://user-images.githubusercontent.com/129272853/230951541-e69c9e58-29f7-4203-9569-83d996c0a911.png)



## 3. DIRECT

__example:__

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

![sevendegment_DIRECT](https://user-images.githubusercontent.com/129272853/230951488-9f96c7fb-34de-475f-9cd7-701c128f3fbb.png)


The above 3 examples are tested on the Atmega32 microcontroller.

**Note:**
All connections and functions are the same in stm32f103r6 microcontroller.





