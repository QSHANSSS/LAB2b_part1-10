#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "register.h"
#define QTPY_BOOT_PIN 21
#define QTPY_BOOT_PIN_BITMASK 0x200000
#define GPIO_IN_OFFSET 0x4
#define QTPY_BOOT_PIN 21
//#define GPIO_REGISTER_BASE 0x40014000
#define LENGTH 100
#define RECORDING_ITERATION 10
/*typedef struct {
    int data[LENGTH];
    int index;
    uint8_t num;
} storage;

typedef struct {
    volatile uint32_t* address;
    uint32_t mask;
    bool binary;
} reg;

typedef struct {
    bool key_mode;
    bool serial_mode;
    bool reg_mode;
}mode_choose;*/

typedef struct Flashlight{
    uint32_t last_serial_byte;
    uint32_t button_is_pressed;
    uint32_t light_color;
    char color[10];
    char key_status[10];
    //struct Flashlight* next;
} Flashlight; 
 //Flashlight* head;


void render_to_console(Flashlight status) {
    // adjust console window height to match 'frame size'
    //printf("button_is_pressed:  0x%08x\n",   status.button_is_pressed);
     printf("button status is: ");
     puts(status.key_status);
    //for(int i=0; i<=strlen(status->key_status);i++)
        //printf("%c",  status->key_status[i]);
    printf("\nLED color is: ");
    puts(status.color);
    //for(int i=0; i<=sizeof(status->color);i++)
       // printf("%c",   status->color[i]);
    printf("\n");
}  

/*bool sequencer(reg* input, storage* buff, uint32_t serial, mode_choose mode) {
    bool full_flag = 0;
    uint32_t val;
    if (mode.key_mode) {
        val = 0x00000001;
        //write_event_to_storage(input, val, mode_choose.mode);
    }
    if (mode.serial_mode) {
       // write_event_to_storage(input, serial, mode_choode.mode);
    }
    if(mode.reg_mode) {
    }
    return !full_flag;
}*/

void print_status_liknedlist(Flashlight *element) {	
    int i=0;
	while (i++<RECORDING_ITERATION) {
        printf("**********************sequential status%d********************",i);
		printf("s byte storage serial: 0x%08x\n", i,element[i].last_serial_byte);
        printf("register value of button gpio: 0x%08x\n", element[i].button_is_pressed);
        printf("button status:");
        puts(element[i].key_status);
        printf("register value of neopixel:0x%08x\n",element[i].light_color);
        printf("neopixel color:");
        puts(element[i].color);
        printf("*****************************************************\n\n");
	}
}


int main() {
    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();
    u_int8_t count=0;
    while(!stdio_usb_connected());
    
    Flashlight status;
    status.last_serial_byte =  0x00000000;
    status.button_is_pressed = 0x00000000;
    status.light_color =       0x0000ff00;
    strcpy(status.color,"green");
    strcpy(status.key_status,"no press");
    neopixel_set_rgb(status.light_color); //change neopixel according to key/console command
    render_to_console(status);
    while (true) {
        Flashlight new_status;//=(Flashlight*)malloc(sizeof(Flashlight));
        Flashlight store[RECORDING_ITERATION]; //recording reg
        new_status.last_serial_byte = getchar_timeout_us(0); // read r,g,b coomand from serial console
        switch(new_status.last_serial_byte) { // poll every cycle
            case 'r':
                new_status.light_color = 0x00ff0000;
                strcpy(new_status.color,"red");
                break;
            case 'g':
                new_status.light_color = 0x0000ff00;
                strcpy(new_status.color,"green");
                break;
            case 'b':
                new_status.light_color = 0x000000ff;
                strcpy(new_status.color,"blue");
                break;
            case 'w':
                new_status.light_color = 0x00ffffff;
                strcpy(new_status.color,"white");
                break;
            case 'p':
                printf("sequential reg values in last 10 status are below:\n");
                print_status_liknedlist(store); //print recording status on serial
                break;
            default: 
                new_status.light_color = 0x00ff00;
                strcpy(new_status.color,"green");
        }
        sleep_ms(100);
        if (gpio_get(QTPY_BOOT_PIN)) { // poll every cycle, 0 = "pressed"
            new_status.button_is_pressed = 0x00000000;
            strcpy(new_status.key_status,"no press");
        } else {
            new_status.button_is_pressed = 0x00000001;
            strcpy(new_status.key_status,"preesed");
        }
        if (new_status.button_is_pressed) { // poll every cycle
            new_status.light_color=0xffffffff;
            strcpy(new_status.color,"white");
        } else {
            //new_status.light_color=0x000000ff;
            //new_status.color="blue";
            ;
        }
        neopixel_set_rgb(new_status.light_color); //change neopixel according to key/console command
        render_to_console(new_status);


        
        for(int i=0;i<RECORDING_ITERATION-1;i++)
            store[i]=store[i+1];
        store[RECORDING_ITERATION-1]=new_status;
        sleep_ms(200); // don't DDOS the serial console
    }
    return 0;
}                  
