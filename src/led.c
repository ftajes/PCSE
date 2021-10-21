#include "led.h"

void ledEncender(gpioMap_t led) //Enciende el led 
{
  gpioWrite( led, ON ); 
}

void ledApagar(gpioMap_t led) //Apaga el led 
{
  gpioWrite( led, OFF ); 
}

bool ledEstado(gpioMap_t led){ //Estado del led
   return gpioRead( led );
}

void ledParpadeo(gpioMap_t led, int tiempo){//Parpadeo del led x tiempo Bloqueante
   gpioWrite( led, ON);
   delay(tiempo);
   gpioWrite( led, OFF);
   delay(tiempo);
}

void ledCondicionesInicio(void){ //Condiciones de los leds al iniciar el micro
   ledApagar(LED1);
   ledApagar(LED2);
   ledApagar(LED3);
   ledApagar(LEDR);
   ledApagar(LEDG);
   ledApagar(LEDB); 
}
 

