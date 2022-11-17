#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
int gpio_in_sample(uint32_t offset){

    volatile uint32_t* address=GPIO_REGISTER_BASE+offset;

    printf("%08x\n",*address);
    printf("===============================\n");
    //sleep_ms(500);
    return *address;
}

int readbit(int reg_val, int shift_bit)
{
    int pin_mask;
    int pin_state;
    int shifted_pin_state;
    pin_mask = 1u << shift_bit;                       
    pin_state = reg_val & pin_mask; 
    shifted_pin_state = pin_state >> shift_bit;
    printf("%d\n",shifted_pin_state);
    printf("===============================\n"); 
    return shifted_pin_state;       
}

void write_gpio(uint32_t offset, int value){
    volatile uint32_t* address=GPIO_REGISTER_BASE+offset;
    *address = value;
}