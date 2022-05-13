#pragma once
#include <Arduino.h>


class buttonleds
{
public:
    buttonleds(/* args */);
    ~buttonleds();
private:
     void setButtonLeds();
    void buttonBreathe();
    unsigned long ledpace  = 50;
    unsigned long ledtimer = 0;
    uint8_t ledlevel       = 100;
    int ledlevelincrement = 1;
};

buttonleds::buttonleds(/* args */)
{
}
