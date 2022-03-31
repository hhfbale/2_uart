#include "uart.h"
#include "gpio.h"

void uart_init(){
    gpio_init();
    GPIO0->PIN_CNF[6] = 0;
    GPIO1->PIN_CNF[8] = 1;

    UART->PSEL_TXD = 0X06;
    UART->PSEL_RXD = 0X28;

    UART->BAUDRATE = 0x00275000;

    UART->PSEL_RTS = (1<<31);
    UART->PSEL_CTS = (1<<31);

    UART->ENABLE = 0x4;

    UART->TASK_STARTRX = 1;


}

void uart_send(char letter){
    
    UART->TASK_STARTTX = 1;

    UART->TXD = letter;

    while(!UART->EVENT_TXDRDY){}

    UART->EVENTS_TXDRDY = 0;

    UART->TASK_STOPTX = 1;


}

char uart_read(){

    if(UART->RXDRDY){
        char letter = UART->RDX;
        UART->EVENTS_RXDRDY = 0;
        return letter;
    }
    else{
        return '\0';
    }

}