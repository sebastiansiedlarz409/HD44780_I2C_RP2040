#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

int main() {
    stdio_init_all();
    
    //init i2c0
    i2c_init(i2c1, 100 * 1000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);

    while(1){

    }
}
