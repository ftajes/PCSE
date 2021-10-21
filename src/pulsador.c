#include "pulsador.h"

static int contador = 0; //Suma 1 cada vez que se detecta que la tecla esta pulsada

bool estadoPulsador(gpioMap_t tecla){//Se obtiene el estado del pulsador
      bool estado = false;
      if(!gpioRead(tecla) ){
         if(contador >= 100){
            if( !gpioRead(tecla) ){
               estado = true;
            }//END Tercer IF
            contador = 0;
         }//END Segundo IF
      contador++;
      }//END Primer IF
      return estado; 
}