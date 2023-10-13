#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include "DIO_INTERFACE.h"
#include "UART_INTERFACE.h"
#include "EXIT_INT_INTERFACE.h"


void turn_on_led(void);
void turn_off_led(void);

volatile unsigned char button_state;  // global variable to detect the reading of switch


int main(void){
	USART_Init();  // Initialize UART
  INT0_init(); // Initialize external interrupt INT0
  sei();  // Enable global interrupts
	  
    // Set PB5 (LED) as output
   DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);
   	// set the switch pin as input
	DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	// activate the internal pull up resistance
	DIO_u8SetPinValue(DIO_PORTD,DIO_PIN2,DIO_PIN_HIGH );
  
   // Set PIND1 as output (for TX)
   DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);

    // Clear PINDD0 as input (for RX)
    DIO_u8SetPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT );
	
	  unsigned char led_state = 0; // flag to detect the led state
 while(1){
		
	      
			
        UART_ReceiveString_ASYNCH();
				 // Transmit received data over UART
				UART_transmitString("Data received: ");
				UART_transmitString(receivedString);
        USART_Transmit('\n');
				
          // Check if the received UART data is valid
				char valid_input =is_valid_uart_input( receivedString);
				if (valid_input) {
         
					if (strcmp( receivedString, "ledon") == 0) {
             UART_transmitString("valid input\n");
            // Check if the LED is already on
						if (led_state) {
							UART_transmitString("The LED is already on.\n");
							} else {
							// Turn on the LED
							turn_on_led();
              
							led_state = 1; // Update LED state
						}
						} else if (strcmp(receivedString, "ledoff") == 0) {
               UART_transmitString("valid input\n");
						
						// Check if the LED is already off
						if (!led_state) {
							UART_transmitString("The LED is already off.\n");
							} else {
							// Turn off the LED
							turn_off_led();
							led_state = 0; // Update LED state
						}
						
					}
					 else {
						UART_transmitString("invalid inputs\n");
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
ISR(INT0_vect) {

 
  unsigned char button_reading=DIO_u8GetPinValue(DIO_PORTD,DIO_PIN2,&button_state);
	if(button_state==1){UART_transmitString("button pressed\n");}
  
}

ISR(USART_RX_vect) {
	char receivedChar = UDR0;  // Read the received character from the USART data register (UDR0)

	if (receivedChar == '\n' || receivedChar == '\r') {
		receivedString[stringIndex] = '\0';  // Null-terminate the received string
		stringComplete = 1;  // Set the flag to indicate that the string is complete
		} else if (stringIndex < BUFFER_SIZE - 1) {
		receivedString[stringIndex] = receivedChar;  // Store the received character in the buffer
		stringIndex++;  // Increment the buffer index
	}
}
