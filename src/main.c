#include "fsm.h"

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */

int main(void){

   /* ------------- INICIALIZACIONES ------------- */
   //AGREGAR CONDICIONES DE INICIO 
   fsmModosFuncionamientoCondicionesInicio();
   
   while(1){
      fsmModosFuncionamientoActualizar();
   }
   return 0;
}//END main


/*==================[end of file]============================================*/