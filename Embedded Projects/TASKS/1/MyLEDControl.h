#ifndef MYLEDCONTROL_H
#define MYLEDCONTROL_H

#include "LPC21xx.h"

class MyLEDControl {
public:
    MyLEDControl(unsigned int pin);
    void init();
    void start();
private:
    unsigned int pin;
    static MyLEDControl* instance;
    void configure_timer();
    static void timer_callback();
};

#endif // MYLEDCONTROL_H
