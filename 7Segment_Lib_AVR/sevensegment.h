
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     CodeVisionAVR
 * @brief   SevenSegment driver library (.h) 
*/

#ifndef __SEVENSEGMENT_H__
#define __SEVENSEGMENT_H__

#include <mega32.h>


/**communication protocol define**/

#define spi                 0x10
#define bcd                 0x11
#define direct              0x12


/**sevensegment type define**/

#define cc                  0x20
#define ca                  0x21


/**dataport and controlport define**/

#define data_port           PORTD
#define control_port        PORTC 


/**stcp pins for data latching in 74hc595 ic**
stcp_C_pin: latch control port 
stcp_D_pin: latch data port**/

#define stcp_C_pin          PORTA.0
#define stcp_D_pin          PORTA.1

/**
 * @brief  To display the number on sevensegment
 * @brief  This function must be executed continuously (with delay 5ms)
 * @param  Number: The number displayed on the sevensegment
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
 * @brief  Initializes SPI Protocol (When the SPI protocol is selected)
 * @param  None
 * @retval None
 */
void SevenSegment_SPI_Init(void);

/**
 * @brief  SevenSegment_Blink
 * @brief  This function can be executed one time
 * @param  Blink_Delay: Toggle time = Blink_Delay * SevenSegment_Write function execution time
 * @retval None
 */
void SevenSegment_Blink_On(unsigned int Blink_Delay);

/**
 * @brief  Turn off blinking
 * @brief  This function can be executed one time
 * @param  None
 * @retval None
 */
void SevenSegment_Blink_Off(void);


#pragma library sevensegment.lib

#endif

