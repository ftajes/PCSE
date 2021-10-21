#include "portI2C.h"


#define DEFAULT_I2C I2C0
#define SPEED_100KHZ 100000


void portI2Cinit()
{
	i2cInit( DEFAULT_I2C, SPEED_100KHZ );
}

void portLcdInit( uint16_t rows, uint16_t columns, uint16_t pixelH, uint16_t pixelV )
{
   lcdInit( rows,  columns, pixelH,  pixelV );
}
              
void driverGpioWrite(pcf8574T_gpio_t pin, bool_t valor){
   pcf8574TGpioWrite( pin, valor);
}

void portDelay_us(uint32_t us)
{
   lcdDelay_us(us);
}

void portDelay_ms(uint32_t ms)
{
   delay(ms);
}



