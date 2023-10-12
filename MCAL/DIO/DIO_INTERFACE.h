#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_



#define DIO_PORTB              1
#define DIO_PORTC              2
#define DIO_PORTD              3
				               
#define DIO_PIN0               0
#define DIO_PIN1               1
#define DIO_PIN2               2
#define DIO_PIN3               3
#define DIO_PIN4               4
#define DIO_PIN5               5
#define DIO_PIN6               6
#define DIO_PIN7               7

#define DIO_PIN_OUTPUT         1
#define DIO_PIN_INPUT          0
						       


#define DIO_PIN_HIGH           1
#define DIO_PIN_LOW            0
unsigned char DIO_u8SetPinDirection(unsigned char copy_Port, unsigned char copy_PinNumber,unsigned char copy_PinDirection);
unsigned char DIO_u8SetPinValue(unsigned char copy_Port, unsigned char  copy_PinNumber,unsigned char  copy_PinValue);
unsigned char DIO_u8GetPinValue(unsigned char copy_Port, unsigned char copy_PinNumber,unsigned char* copy_pReturnValue);
#endif