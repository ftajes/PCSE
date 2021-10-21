#include "fsm.h"
#include "led.h"
#include "pulsador.h"
#include "sapi.h"
#include "display.h"
#include "portI2C.h"

#define FILAS 2
#define COLUMNAS 16
#define PIXEL_H 5
#define PIXEL_V 8
#define RETARDO 200

typedef enum { //Modos de funcionamiento de la Planta
      PARADA_EMERGENCIA,
      REINICIAR,
      AUTOMATICO,
      STOP,
      SEMIAUTOMATICO
} fsmModosFuncionamiento_t;

static fsmModosFuncionamiento_t fsmModosFuncionamiento;

static void fsmModosFuncionamientoError( void );

void fsmModosFuncionamientoActualizar(void){
   limpiarPantalla();
   printPantalla("E-STOP");
   /* Variables para Retardo no bloqueante */
   delay_t delays;
   uint8_t led = OFF;
   /*Se inicializa Retardo no bloqueante (200ms = 0,2s) */
   delayConfig( &delays, RETARDO);
   /* ------------- LOOP ------------- */
   while(1) {

      switch( fsmModosFuncionamiento ){

         case PARADA_EMERGENCIA:   /* PARADA DE EMERGENCIA */
         //Parpadeo del LED2 cada 200ms
         if ( delayRead( &delays ) ){
            if( !led )
               led = ON;
            else
               led = OFF;
            gpioWrite( LED2, led );
         }//END IF Parpadeo 
            //REINICIAR
            if (estadoPulsador(TEC2)){
               ledApagar(LED2);
               limpiarPantalla();
               printPantalla("RESET");
               fsmModosFuncionamiento = REINICIAR;
            }
         break;

         case REINICIAR:  /* RESET */ 
            ledEncender(LED1);
            //SEMIAUTOMATICO
            if (estadoPulsador(TEC4)){
               ledApagar(LED1);
               limpiarPantalla();
               printPantalla("SEMIAUTOMATICO");
               fsmModosFuncionamiento = SEMIAUTOMATICO;
            }
            //AUTOMATICO
            if (!estadoPulsador(TEC2) && estadoPulsador(TEC3)){
               ledApagar(LED1);
               limpiarPantalla();
               printPantalla("AUTOMATICO");
               fsmModosFuncionamiento = AUTOMATICO;
            }
            //PARADA DE EMERGENCIA
            if (estadoPulsador(TEC1)){
               ledApagar(LED1);
               limpiarPantalla();
               printPantalla("E-STOP");
               fsmModosFuncionamiento = PARADA_EMERGENCIA;
            }
         break;

         case AUTOMATICO:  /* AUTOMATICO */    
            ledEncender(LED3);
            if (estadoPulsador(TEC4)){
               ledApagar(LED3);               
               limpiarPantalla();
               printPantalla("STOP");
               fsmModosFuncionamiento = STOP;
            }
            //PARADA DE EMERGENCIA
            if (estadoPulsador(TEC1)){
               ledApagar(LED3);
               limpiarPantalla();
               printPantalla("E-STOP");
               fsmModosFuncionamiento = PARADA_EMERGENCIA;
            }
         break;
         
         case STOP:  /* STOP */
            ledEncender(LED2);
            if (estadoPulsador(TEC3)){
               ledApagar(LED2);
               limpiarPantalla();
               printPantalla("SEMIAUTOMATICO");
               fsmModosFuncionamiento = SEMIAUTOMATICO;
            }
            // REINICIAR
            if (estadoPulsador(TEC2)){
               ledApagar(LED2);
               limpiarPantalla();
               printPantalla("RESET");
               fsmModosFuncionamiento = REINICIAR;
            }
            //PARADA DE EMERGENCIA
            if (estadoPulsador(TEC1)){
               ledApagar(LED2);
               limpiarPantalla();
               printPantalla("E-STOP");
               fsmModosFuncionamiento = PARADA_EMERGENCIA;
            } 
         break;
         
         case SEMIAUTOMATICO:  /* SEMIAUTOMATICO */    
            ledEncender(LEDB);
            //PARADA DE EMERGENCIA
            if (estadoPulsador(TEC1)){
               ledApagar(LEDB);
               limpiarPantalla();
               printPantalla("E-STOP");
               fsmModosFuncionamiento = PARADA_EMERGENCIA;
            }
         break;

         default:
            fsmModosFuncionamientoError(); 
         break;
      }//END switch
   }//END WHILE
}//END fsmModosFuncionamiento

void fsmModosFuncionamientoCondicionesInicio(void){
   boardInit();
   portI2Cinit();
   // Inicializar LCD de 16x2 (columnas x filas) con cada caracter de 5x8 pixeles
   portLcdInit( COLUMNAS, FILAS, PIXEL_H, PIXEL_V );
   ledCondicionesInicio();
   fsmModosFuncionamiento = PARADA_EMERGENCIA;
}

static void fsmModosFuncionamientoError( void )
{
   fsmModosFuncionamiento = PARADA_EMERGENCIA;
   printPantalla("DEFAULT PE");
}


