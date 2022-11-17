#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
int gpio_in_sample(uint32_t offset);
int readbit(int reg_val, int shift_bit);
void write_gpio(uint32_t offset, int value);