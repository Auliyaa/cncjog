#pragma once

#include <action.h>

struct action_move_t: public action_t
{
    virtual void btn_clicked(uint8_t pin);
    virtual void encoder_moved(int position);
    virtual void encoder_clicked();
};