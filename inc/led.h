#include "sapi.h"

void ledEncender(gpioMap_t led); //Enciende el led 
void ledApagar(gpioMap_t led); //Apaga el led 
bool ledEstado(gpioMap_t led); //Estado del led
void ledParpadeo(gpioMap_t led, int tiempo); //Parpadeo del led x tiempo
void ledCondicionesInicio(void);
