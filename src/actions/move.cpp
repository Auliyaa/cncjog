#include <actions/move.h>

#include <pins.h>
#include <screen.h>

void action_move_t::btn_clicked(uint8_t pin)
{
    if (pin == PIN_BTN_X) screen->axis_cur = AXIS_X;
    else if (pin == PIN_BTN_Y) screen->axis_cur = AXIS_Y;
    else if (pin == PIN_BTN_Z) screen->axis_cur = AXIS_Z;
    else if (pin == PIN_BTN_S) screen->axis_cur = AXIS_S;
}

void action_move_t::encoder_moved(int position)
{

}

void action_move_t::encoder_clicked()
{

}
