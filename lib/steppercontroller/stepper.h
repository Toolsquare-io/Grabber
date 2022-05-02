#pragma once

enum class direction{
    clockwise,
    counterclockwise
};

class stepper
{
public:
    stepper();
    void setPins(int pPin, int dPin);
    void setDir(direction dir);
    void step();
    long getDelta();
private:
    int pulsePin;
    int dirPin;
    long delta;
    direction theDirection;
};

