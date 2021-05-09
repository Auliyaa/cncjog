#include <Arduino.h>

#include <actions/move.h>

#include <pins.h>
#include <screen.h>
#include <button.h>
#include <encoder.h>

// list of modes


// init onboard devices
screen_t screen(PIN_SCREEN_RST);
encoder_t enc;

btn_t btn_m(PIN_BTN_M);

#define BTNS_CNT 4
btn_t btns[] = { btn_t(PIN_BTN_X), btn_t(PIN_BTN_Y), btn_t(PIN_BTN_Z), btn_t(PIN_BTN_S) };

#define ACTIONS_CNT 1
action_t* actions[] = {
  new action_move_t()
};
size_t action_current = 0;

int encoder_pos=0;

void setup()
{
  Serial.begin(9600);
  
  btn_m.setup();

  screen.setup();
  enc.setup(PIN_ENCODER_DT, PIN_ENCODER_CLK, PIN_ENCODER_SW);

  for (size_t ii=0; ii < BTNS_CNT; ++ii)
  {
    btns[ii].setup();
  }

  for (size_t ii=0; ii < ACTIONS_CNT; ++ii)
  {
    actions[ii]->screen = &screen;
    actions[ii]->setup();
  }
}

void loop()
{
  for (size_t ii=0; ii < BTNS_CNT; ++ii)
  {
    if (btns[ii].read())
    {
      Serial.print("Button clicked: ");
      Serial.println(btns[ii].pin);
      actions[action_current]->btn_clicked(btns[ii].pin);
    }
  }

  enc.read();
  int p = enc.pos();
  if (enc.pos() != encoder_pos)
  {
    Serial.print("Encoder moved: ");
    Serial.println(encoder_pos - p);
    actions[action_current]->encoder_moved(encoder_pos - p);
    encoder_pos = p;
  }

  screen.draw();
}