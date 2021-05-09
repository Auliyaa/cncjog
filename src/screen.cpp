#include <screen.h>

#include <stdlib.h>

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SPLASH_DURATION 100

screen_t::screen_t(uint8_t rst)
    : display{new Adafruit_SSD1306(128, 32, &Wire, rst)}, // 128x32px, RST pin=4,
      axis_pos{0,0,0}, axis_incr{10}, axis_cur{AXIS_X},
      icon(nullptr), user_text(nullptr), user_text_sz(0)
{
}

screen_t::~screen_t()
{
}

bool screen_t::setup()
{
    if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        return false;
    }

    display->display();
    delay(SPLASH_DURATION);
    display->clearDisplay();
    display->display();

    return true;
}

void screen_t::draw()
{
    display->clearDisplay();
    for (size_t ai=0; ai<3; ++ai)
    {
        memset(draw_buf_xyz, 0, SCREEN_DRAW_BUF_XYZ_SZ);
        draw_buf_xyz[0] = 'X'+ai;
        draw_buf_xyz[1] = ':';
        draw_buf_xyz[2] = ' ';
        dtostrf(axis_pos[ai], 7, 2, draw_buf_xyz+3);
        if (ai==axis_cur)
        {
            draw_buf_xyz[10]=' ';
            draw_buf_xyz[11]='*';
        }
        draw_text(0,ai*10,draw_buf_xyz,strlen(draw_buf_xyz));
    }

    memset(draw_buf_xyz, 0, SCREEN_DRAW_BUF_XYZ_SZ);
    draw_buf_xyz[0] = (axis_cur == AXIS_S ? '!' : ' ');
    
    dtostrf(axis_incr, 7, 2, draw_buf_xyz+1);
    draw_text(80,0,draw_buf_xyz,strlen(draw_buf_xyz));

    // TODO: icon
    // TODO: user_text

    display->display();
}

void screen_t::draw_text(int x, int y, const char* txt, int sz)
{
    display->setTextSize(1);              // Normal 1:1 pixel scale
    display->setTextColor(SSD1306_WHITE); // Draw white text
    display->setCursor(x, y);             // Start at top-left corner
    display->cp437(true);                 // Use full 256 char 'Code Page 437' font

    for (int ii=0; ii < sz; ++ii)
    {
        display->write(txt[ii]);
    }
}