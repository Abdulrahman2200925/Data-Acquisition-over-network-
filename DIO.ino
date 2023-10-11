
#include <avr/io.h>
#include "BIT.h"
#include "DIO_INTERFACE.h"

#define OK  0
#define NOK 1
unsigned char DIO_u8SetPinDirection(unsigned char copy_u8Port, unsigned char copy_u8PinNumber,unsigned char copy_u8PinDirection)
{
	unsigned char Local_u8ErrorState=OK;
	
	if(copy_u8PinNumber<=DIO_PIN7)
	{
		if(copy_u8PinDirection == DIO_PIN_OUTPUT){
			switch(copy_u8Port)
			{
				
				case DIO_PORTB : SET_BIT(DIO_REG_DDRB,copy_u8PinNumber);  break;
				case DIO_PORTC : SET_BIT(DIO_REG_DDRC,copy_u8PinNumber);  break;
				case DIO_PORTD : SET_BIT(DIO_REG_DDRD,copy_u8PinNumber);  break;
				default:Local_u8ErrorState=NOK; break;
			}
		}
		else if(copy_u8PinDirection == DIO_PIN_INPUT)
		{
			switch(copy_u8Port)
			{
			
				case DIO_PORTB: CLR_BIT(DIO_REG_DDRB,copy_u8PinNumber);  break;
				case DIO_PORTC: CLR_BIT(DIO_REG_DDRC,copy_u8PinNumber);  break;
				case DIO_PORTD: CLR_BIT(DIO_REG_DDRD,copy_u8PinNumber);  break;
				default:Local_u8ErrorState=NOK; break;
				}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
		
	}
	else
	{
		
		Local_u8ErrorState=NOK;
		
	}
	
	

	return Local_u8ErrorState;

}

unsigned char DIO_u8SetPinValue(unsigned char copy_u8Port, unsigned char  copy_u8PinNumber,unsigned char  copy_u8PinValue)
{
 unsigned char Local_u8ErrorState=OK;
	if(copy_u8PinNumber<=DIO_PIN7)
	{
		if(copy_u8PinValue == DIO_PIN_HIGH)
		{
			switch(copy_u8Port)
			{
				
				case DIO_PORTB: SET_BIT(DIO_REG_PORTB,copy_u8PinNumber);  break;
				case DIO_PORTC: SET_BIT(DIO_REG_PORTC,copy_u8PinNumber);  break;
				case DIO_PORTD: SET_BIT(DIO_REG_PORTD,copy_u8PinNumber);  break;
				default:Local_u8ErrorState=NOK; break;
			}
		}
		else if(copy_u8PinValue == DIO_PIN_LOW)
		{
			switch(copy_u8Port)
			{
				
				case DIO_PORTB: CLR_BIT(DIO_REG_PORTB,copy_u8PinNumber);  break;
				case DIO_PORTC: CLR_BIT(DIO_REG_PORTC,copy_u8PinNumber);  break;
				case DIO_PORTD: CLR_BIT(DIO_REG_PORTD,copy_u8PinNumber);  break;
				default:Local_u8ErrorState=NOK; break;
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
		
	}else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
	
}


 
 unsigned char  DIO_u8GetPinValue( unsigned char copy_u8Port,  unsigned char copy_u8PinNumber, unsigned char* copy_pu8ReturnValue)
{
	 unsigned char Local_u8ErrorState=OK;
	if(copy_u8PinNumber<=DIO_PIN7)
	{
		switch(copy_u8Port)
		{
			
			case DIO_PORTB:  *copy_pu8ReturnValue = GET_BIT(DIO_REG_PINB,copy_u8PinNumber); break;
			case DIO_PORTC:  *copy_pu8ReturnValue = GET_BIT(DIO_REG_PINC,copy_u8PinNumber); break;
			case DIO_PORTD:  *copy_pu8ReturnValue = GET_BIT(DIO_REG_PIND,copy_u8PinNumber); break;
			default:Local_u8ErrorState=NOK; break;
		}
		
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	
	
	
	return Local_u8ErrorState;
}