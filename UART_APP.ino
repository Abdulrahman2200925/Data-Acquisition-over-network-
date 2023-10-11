#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include "DIO_INTERFACE.h"
#include "UART_INTERFACE.h"





//extern char receivedString[BUFFER_SIZE];
void turn_on_led(void);
void turn_off_led(void);
int main(void){
	USART_Init();  // Initialize UART
  INT0_init(); // Initialize external interrupt INT0
  sei();  // Enable global interrupts
	  
    // Set PB5 (LED) as output
   DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);
   // set the switch pin as output
   DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
   // set the switch as pull down
   DIO_u8SetPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_LOW );
  
   // Set PD1 as output (for TX)
   DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);

    // Clear PD0 as input (for RX)
    DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT );
	
	  unsigned char led_state = 0; // flag to detect the led state
while(1){
		
	      // Receive UART data into uart_data buffer
			
        UART_ReceiveString_ASYNCH();
				 // Transmit received data over UART
				UART_transmitString("Data received: ");
				UART_transmitString(receivedString);
				USART_Transmit('\r');
          // Check if the received UART data is valid
				char valid_input =is_valid_uart_input( receivedString);
				if (valid_input==1) {
          UART_transmitString("valid input\r");
					if (strcmp( receivedString, "ledon") == 0) {
            // Check if the LED is already on
						if (led_state) {
							UART_transmitString("The LED is already on.");
							} else {
							// Turn on the LED
							turn_on_led();
              
							led_state = 1; // Update LED state
						}
						} else if (strcmp(receivedString, "ledoff") == 0) {
						
						// Check if the LED is already off
						if (!led_state) {
							UART_transmitString("The LED is already off.");
							} else {
							// Turn off the LED
							turn_off_led();
							led_state = 0; // Update LED state
						}
						
					}
					else{
						UART_transmitString("invalid inputs");
					}

					
					
					
					//  small delay to stabilize
					_delay_ms(100);
				}
				
			}
	
	
}
void turn_on_led(void){
   DIO_u8SetPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_HIGH );
}
void turn_off_led(void){
  DIO_u8SetPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
}
