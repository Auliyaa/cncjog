#pragma once

#include <Arduino.h>

struct btn_t
{
    uint8_t pin;
    uint8_t state;

    inline btn_t(uint8_t p)
        : pin(p)
    {
    }

    inline void setup()
    {
        pinMode(pin, INPUT);
    }

    inline bool read()
    {
        int s = digitalRead(pin);
        bool r = state == LOW && s == HIGH;
        state = s;
        return r;
    }
};