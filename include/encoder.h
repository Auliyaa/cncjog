#pragma once

#include <Arduino.h>

struct encoder_t
{
    void setup(uint8_t dt, uint8_t clk, uint8_t sw)
    {
        _pin_dt = dt;
        _pin_clk = clk;
        _pin_sw = sw;

        _position = 0;
        _pushed = false;

        _last_clk = HIGH;
        _last_dt = HIGH;
        _last_sw = HIGH;

        pinMode(_pin_clk, INPUT_PULLUP);
        pinMode(_pin_dt, INPUT_PULLUP);
        pinMode(_pin_sw, INPUT_PULLUP);
    }

    void read()
    {
        int clk = digitalRead(_pin_clk);
        int dt = digitalRead(_pin_dt);
        int sw = digitalRead(_pin_sw);
        
        if (_last_clk == LOW && clk == HIGH)
        {
            if (dt == LOW) --_position;
            else ++_position;
        }

        _pushed = (sw == LOW && _last_sw == HIGH);

        _last_sw = sw;
        _last_dt = dt;
        _last_clk = clk;
    }

    int pos() const
    {
        return _position;
    }

    bool pushed() const
    {
        return _pushed;
    }

private:
    uint8_t _pin_dt;
    uint8_t _pin_clk;
    uint8_t _pin_sw;

    int _position;
    bool _pushed;

    int _last_clk;
    int _last_dt;
    int _last_sw;
};
