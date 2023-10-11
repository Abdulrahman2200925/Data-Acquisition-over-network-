

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "BIT.h"
#include "UART_INTERFACE.h"

#define BUFFER_SIZE 64
// Global variable to store UART data (volatile used to avoid the complier optimization because it will be accessed by isr)
 volatile char receivedString[BUFFER_SIZE];
 volatile unsigned char  stringIndex;
 volatile unsigned char stringComplete;

void USART_Init(void) {
	unsigned short int baud_rate = ((F_CPU/ (BAUD *16UL) - 1)) ;
	// SETTING THE BAUD RATE IN THE REGISTERS // 
	UBRR0L = (unsigned char)(baud_rate );
	UBRR0H = (unsigned char)(baud_rate >> 8);
 // Enable receiver and transmitter
	SET_BIT(UCSR0B,RXEN0);
	SET_BIT(UCSR0B,TXEN0);
 // Set frame format: 8 data bits, 1 stop bit, no parity
	SET_BIT(	UCSR0C,UCSZ01);
	SET_BIT(UCSR0C,UCSZ00);
 // enable the reciver interrupt //
  SET_BIT(UCSR0B, RXCIE0);  
}

void USART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
	UDR0 = data; // Put data into buffer and send
}
void UART_ReceiveString_ASYNCH() {
	stringIndex = 0;
	stringComplete = 0;
	unsigned char i;
	// Initialize received string to all null characters
	for ( i = 0; i < BUFFER_SIZE; i++) {
		receivedString[i] = '\0';
	}
	

	// Wait for the string to be received
	while (!stringComplete) {
		
	}
	

}

void UART_receiveString(char *str, unsigned char maxLength) {
	unsigned char i = 0;
	while (i < (maxLength - 1)) {
		while (!(UCSR0A & (1 << RXC0))); // Wait for data to be received
		unsigned char receivedByte = UDR0; // Read the received byte
		
		// Check for end of string
		if (receivedByte == '\0' || receivedByte == '\n' || receivedByte == '\r') {
			break;
		}
		
		str[i++] = receivedByte;
	}
	str[i] = '\0'; // Null-terminate the string
}
void UART_transmitString(const char *str) {
	while (*str != '\0') {
		while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
		UDR0 = *str; // Transmit the character
		str++;
	}
}


unsigned char is_uppercase(const char* str) {
	for (int i = 0; str[i]; i++) {
		if (!(str[i] >= 'A' && str[i] <= 'Z')) {
			return 0; // Not entirely uppercase
		}
	}
	return 1; // Entirely uppercase
}
unsigned char is_whitespace(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
			return 0; // Not empty, contains non-whitespace characters
		}
	}
	return 1; // Empty or contains only whitespace characters
}

unsigned char contains_numbers(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			return 1; // Contains numbers
		}
	}
	return 0; // Does not contain numbers
}
// Function to check if UART input is valid (case-insensitive)
int is_valid_uart_input(const  char* input) {
	
	// List of valid UART commands (lowercase)
	const char* valid_commands[] = {"ledon", "ledoff"};

	unsigned char is_valid = 1; // Initialize the validity flag to true
	unsigned char has_transmitted_message = 0; // Flag to track message transmission

	for (int i = 0; input[i] != '\0'; i++) {
		if (!(input[i] >= 'a' && input[i] <= 'z') &&
		!(input[i] >= 'A' && input[i] <= 'Z') &&
		!(input[i] >= '0' && input[i] <= '9')) {
			if (!has_transmitted_message) {
				UART_transmitString("You are not allowed to use special characters.");
				has_transmitted_message = 1; // Set the flag to indicate the message has been transmitted
			}
			is_valid = 0; // Input contains a disallowed character, not valid
		}
	}
	// Check if input length is valid
	if (strlen(input) > 6) {
		UART_transmitString("invalid data length");
		is_valid = 0; // Invalid input length
	}
	// Check if the input is entirely in uppercase
	if (is_uppercase(input)) {
		UART_transmitString("Use lowercase for commands (ledon/ledoff)");
		is_valid = 0; // Entirely uppercase, not valid
	}
	unsigned char f=contains_numbers(input);
	if (f==1) {
		UART_transmitString("Do not use numbers in commands.");
		is_valid = 0; // Contains numbers, not valid
	}
	unsigned char z=is_whitespace(input);
	if(z==1){
		UART_transmitString("empty command");
	}
	

	return is_valid; // Return the validity flag
}
void INT0_init() {
	
	
  // Enable external interrupt on INT0, trigger on rising edge
   SET_BIT( EICRA,ISC01);
   SET_BIT( EICRA,ISC00);
   
	// Enable external interrupt INT0
	SET_BIT( EIMSK,INT0);
  
}

// External interrupt INT0 ISR
ISR(INT0_vect) {
	unsigned char button_state=GET_BIT(PIND,PIND2);
	if(button_state==1){UART_transmitString("button pressed");}
	//else{UART_transmitString("button not pressed");}
//}
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
