
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     STM32CubeIDE
 * @brief   SevenSegment driver library (.h) 
*/

#ifndef __SEVENSEGMENT_H__
#define __SEVENSEGMENT_H__

#include "main.h"


/**communication protocol define**/

#define spi                 0x10
#define bcd                 0x11
#define direct              0x12


/**sevensegment type define**/

#define cc                  0x20
#define ca                  0x21


/**dataport and controlport define**/

#define data_port           GPIOC
#define control_port        GPIOB


/**Determining the delay between control port and data port based on CPU cycles method**
Note: CPUCLK / CPU_frq_divider = ticks or the number of cycles that CPU waits**/

#define CPU_frq_divider	    40000UL


/**stcp pins for data latching in 74hc595 ic**
stcp_C_pin/port: latch control pin/port 
stcp_D_pin/port: latch data pin/port**/

#define stcp_C_port         GPIOC
#define stcp_D_port         GPIOC
#define stcp_C_pin          GPIO_PIN_0
#define stcp_D_pin          GPIO_PIN_1

/**
 * @brief  To display the number on sevensegment
 * @note   This function must be executed continuously (with delay 5ms or less)
 * @param  Number: The number we want to be displayed in sevensegment
 * @retval None
 */
void SevenSegment_Write(float Number);

/**
 * @brief  Initializes sevensegment
 * @param  Protocol: Select the communication protocol
 * (direct(PIN_0 ... PIN_7: data port, PIN_8: dot point) / bcd(PIN_0 ... PIN_3: data port, PIN_4: dot point) / spi(Like direct protocol))
 * @param  Digits: Select the number of digits (2<= digits <=8)
 * @param  LED_Type: Select the sevensegment LED type (cc / ca)
 * @retval None
 */
void SevenSegment_Init(unsigned char Protocol, unsigned char Digits, unsigned char LED_Type);

/**
 * @brief  SevenSegment_Blink
 * @note   This function can be executed one time
 * @param  Blink_Delay: Toggle time = Blink_Delay * SevenSegment_Write function execution time
 * @retval None
 */
void SevenSegment_Blink_On(unsigned int Blink_Delay);

/**
 * @brief  Turn off blinking
 * @note   This function can be executed one time
 * @param  None
 * @retval None
 */
void SevenSegment_Blink_Off(void);

#endif

