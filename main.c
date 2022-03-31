#include "uart.h" 
#include "gpio.h"
#include <stdio.h>




ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}

int main(){
    
    //iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018,’C’);

    int i = 0;

    uart_init();
    int sleep = 0;
    while(1){

        if(!(GPIO0->IN & (1<<14))){
            uart_send('A');
        }

        if(!(GPIO0->IN & (1<<23))){
            uart_send('B');
        }

        if(uart_read()!='\0'){
            
            switch(i){
                case 0:
                    gpio_lights_on();
                    i = 1;
                    break;
                case 1:
                    gpio_lights_off();
                    i = 0;
                    break;
            }
        }
      
        sleep = 10000;
        while(--sleep);
    }
    return 0;
}

