
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     CodeVisionAVR
 * @brief   SevenSegment driver library (.h) 
*/

#ifndef __SEVENSEGMENT_H__
#define __SEVENSEGMENT_H__

#include <mega32.h>

/** Communication protocol definitions **/
#define SPI                 0x10
#define BCD                 0x11
#define DIRECT              0x12

/** Seven-segment display type definitions **/
#define CC                  0x20
#define CA                  0x21

/** Data port and control port definitions **/
#define DATA_PORT           PORTD
#define CONTROL_PORT        PORTC 

/** STCP pins for data latching in 74HC595 IC
 *  stcp_C_pin: latch control port 
 *  stcp_D_pin: latch data port **/
#define STCP_C_PIN          PORTA.0
#define STCP_D_PIN          PORTA.1

/**
 * @brief  Displays a number on the seven-segment display.
 * @note   This function must be executed continuously (with a delay of 5ms).
 * @param  Number: The number to be displayed on the seven-segment display.
 * @retval None
 */
void SevenSegment_Write(float Number);

/**
 * @brief  Initializes the seven-segment display.
 * @param  Protocol: Selects the communication protocol
 *                  (DIRECT (PIN_0 ... PIN_7: data port, PIN_8: dot point) / 
 *                   BCD (PIN_0 ... PIN_3: data port, PIN_4: dot point) / 
 *                   SPI (like DIRECT protocol)).
 * @param  Digits: Selects the number of digits (2 <= digits <= 8).
 * @param  LED_Type: Selects the seven-segment LED type (CC / CA).
 * @retval None
 */
void SevenSegment_Init(unsigned char Protocol, unsigned char Digits, unsigned char LED_Type);

/**
 * @brief  Initializes the SPI protocol (when the SPI protocol is selected).
 * @param  None
 * @retval None
 */
void SevenSegment_SPI_Init(void);

/**
 * @brief  Blinks the seven-segment display.
 * @note   This function can be executed one time.
 * @param  Blink_Delay: Toggle time = Blink_Delay * SevenSegment_Write function execution time.
 * @retval None
 */
void SevenSegment_Blink_On(unsigned int Blink_Delay);

/**
 * @brief  Turns off blinking of the seven-segment display.
 * @note   This function can be executed one time.
 * @param  None
 * @retval None
 */
void SevenSegment_Blink_Off(void);

#pragma library sevensegment.lib

#endif
