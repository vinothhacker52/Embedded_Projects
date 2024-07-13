#include<lpc21xx.h>
#include<E:\V23CE6V2\EMBEDDED PROJECTS\UART_LCD_ASSIGNMENT\LCD_DRIVER.h>
#include<E:\V23CE6V2\EMBEDDED PROJECTS\UART_LCD_ASSIGNMENT\UART0_DRIVER.h>

int main(){
    unsigned char buffer[100]; // Assuming MAX_LENGTH is defined appropriately
    unsigned char* p = buffer; // Point p to the allocated buffer
    UART0_INIT();
    while(1){
        unsigned char *str = UART0_LCD(p);
        UART0_STR(str);
        LCD_INIT();
        LCD_STR(str);
    }
}
