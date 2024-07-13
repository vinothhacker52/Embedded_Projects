#include "MyLEDControl.h"
#include "MyLEDControl.cpp"

MyLEDControl led(10); // Example using P0.10

extern "C" void startup() {
    led.init();
    led.start();
    
}
int main(){
startup();
while(1);
}
