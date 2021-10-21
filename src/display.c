#include "display.h"
#include "portI2C.h"

#define CMD_BORRAR_PANTALLA 0b00000001
#define DELAY_US 50

void enable(void){
   driverGpioWrite( LCD_HD44780_EN, TRUE  ); // EN = 1    
   portDelay_us(DELAY_US);     
   driverGpioWrite( LCD_HD44780_EN, FALSE  );// EN = 0 
}

void cmdData(void){  
   driverGpioWrite( LCD_HD44780_RS, TRUE  );// RS = 1 para datos
   driverGpioWrite( LCD_HD44780_RW, FALSE  );  
}

void cmdComando(void){
   driverGpioWrite( LCD_HD44780_RS, FALSE  );// RS = 0 comandos
   driverGpioWrite( LCD_HD44780_RW, FALSE  );  
}

void dato(int data){
   cmdData();
   driverGpioWrite( LCD_HD44780_D7, ( data & 0x80 ) );
   driverGpioWrite( LCD_HD44780_D6, ( data & 0x40 ) );
   driverGpioWrite( LCD_HD44780_D5, ( data & 0x20 ));
   driverGpioWrite( LCD_HD44780_D4, ( data & 0x10 ) );
   
   enable();
   
   driverGpioWrite( LCD_HD44780_D7, ( data & 0x08 ) );
   driverGpioWrite( LCD_HD44780_D6, ( data & 0x04 ));
   driverGpioWrite( LCD_HD44780_D5, ( data & 0x02 ) );
   driverGpioWrite( LCD_HD44780_D4, ( data & 0x01 ));
   
   enable();  
}

void printPantalla(char * str){
   uint8_t i = 0;
   while( str[i] != 0 ) {
      dato( str[i] );
      i++;
   }
}

void comando(int data){
   cmdComando();
   driverGpioWrite( LCD_HD44780_D7, ( data & 0x80 ) );
   driverGpioWrite( LCD_HD44780_D6, ( data & 0x40 ) );
   driverGpioWrite( LCD_HD44780_D5, ( data & 0x20 ));
   driverGpioWrite( LCD_HD44780_D4, ( data & 0x10 ) );
   
   enable();
   
   driverGpioWrite( LCD_HD44780_D7, ( data & 0x08 ) );
   driverGpioWrite( LCD_HD44780_D6, ( data & 0x04 ));
   driverGpioWrite( LCD_HD44780_D5, ( data & 0x02 ) );
   driverGpioWrite( LCD_HD44780_D4, ( data & 0x01 ));
   
   enable();  
}

void limpiarPantalla(void){
   comando(CMD_BORRAR_PANTALLA); //Código 0b00000001 borra datos
}
  
