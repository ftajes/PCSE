#include "sapi.h"

void portI2Cinit();
void portLcdInit( uint16_t lineWidth, uint16_t amountOfLines, uint16_t charWidth, uint16_t charHeight );
void driverGpioWrite(pcf8574T_gpio_t pin, bool_t valor);
void portDelay_us(uint32_t us);
void portDelay_ms(uint32_t ms);