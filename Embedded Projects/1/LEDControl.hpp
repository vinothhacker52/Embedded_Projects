#ifndef LEDCONTROL_HPP
#define LEDCONTROL_HPP

class LEDControl {
public:
    LEDControl(unsigned int pin);
    void init();
    void on();
    void off();
    void toggle();

private:
    unsigned int pin;
    void configurePin();
};

#endif // LEDCONTROL_HPP
