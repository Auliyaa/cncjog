#pragma once

#include <Arduino.h>

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2
#define AXIS_S 3

class Adafruit_SSD1306;

struct screen_t
{
    float axis_pos[3];
    float axis_incr;
    size_t axis_cur;

    const char* icon;
    const char* user_text;
    size_t user_text_sz;

    screen_t(uint8_t rst);
    virtual ~screen_t();

    bool setup();
    void draw();

private:
    Adafruit_SSD1306* display;

#define SCREEN_DRAW_BUF_XYZ_SZ 13
    char draw_buf_xyz[SCREEN_DRAW_BUF_XYZ_SZ];

    void draw_text(int x, int y, const char* txt, int sz);
};