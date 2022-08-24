#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#include "lcd_i2c.h"

int main() {
    stdio_init_all();
    
    //init i2c0
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(17, GPIO_FUNC_I2C);
    gpio_set_function(16, GPIO_FUNC_I2C);
    gpio_pull_up(17);
    gpio_pull_up(16);

    LCD_Begin(i2c0,0x27, 2, 16, 1, 1);

    while(1){

    }
}
