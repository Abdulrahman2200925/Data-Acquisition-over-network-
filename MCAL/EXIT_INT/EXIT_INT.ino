#include <avr/io.h>
#include "BIT.h"

void INT0_init() {
	
 
  // Enable external interrupt on INT0, trigger on rising edge
   SET_BIT( EICRA,ISC01);
   SET_BIT( EICRA,ISC00);
   
   SET_BIT( EIMSK,INT0);
  
}
