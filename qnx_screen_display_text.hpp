#pragma once
#include "qnx_screen_display.hpp"
class qnx_screen_display_text : public qnx_screen_display {
private:
    int init_win() {
        int error = qnx_screen_display::init_win();
        if (error) {
            return error;
        }
    }
};