#pragma once

#include <Arduino.h>

struct screen_t;

struct action_t
{
    screen_t* screen;

    virtual void setup() {}

    virtual void btn_clicked(uint8_t pin)=0;
    virtual void encoder_moved(int position)=0;
    virtual void encoder_clicked()=0;
};