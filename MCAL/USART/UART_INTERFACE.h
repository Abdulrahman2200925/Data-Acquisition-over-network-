#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

#define BUFFER_SIZE 64
extern volatile char receivedString[BUFFER_SIZE];   // extern this variable to be used in the main 
extern volatile unsigned char stringIndex;
extern volatile unsigned char stringComplete;

#define BAUD 9600      // change the baud rate as you need //


void USART_Init(void);
void UART_receiveString(char *str, unsigned char maxLength) ;


void UART_ReceiveString_ASYNCH();
void UART_transmitString(const char *str);
void USART_Transmit(unsigned char data);

unsigned char is_uppercase(const char* str);
unsigned char is_whitespace(const char* str);
unsigned char contains_numbers(const char* str);
int is_valid_uart_input(const  char* input);









#endif