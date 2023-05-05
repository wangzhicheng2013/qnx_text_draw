#pragma once
#include "qnx_screen_context.hpp"
class qnx_screen_display {
protected:
    screen_window_t win_ = { 0 };
    int display_zorder_ = 999;
protected:
    int init_win() {
        int error = screen_create_window(&win_, QNX_SCREEN_CTX.screen_ctx);
        if (error) {
            SLOG_E("screen_create_window failed, error:%s", strerror(errno));
            return error;
        }
        static const int vis = 1;
        error = screen_set_window_property_iv(win_, SCREEN_PROPERTY_VISIBLE, &vis);
        if (error) {
            SLOG_E("screen_set_window_property_iv for SCREEN_PROPERTY_VISIBLE failed, error:%s", strerror(errno));
            return error;
        }
        error = screen_set_window_property_pv(win_, SCREEN_PROPERTY_DISPLAY, (void**)&QNX_SCREEN_CTX.screen_disp);
        if (error) {
            SLOG_E("screen_set_window_property_iv for SCREEN_PROPERTY_DISPLAY failed, error:%s", strerror(errno));
            return error;
        }
        static const int usage = SCREEN_USAGE_WRITE;
        error =  screen_set_window_property_iv(win_, SCREEN_PROPERTY_USAGE, &usage);
        if (error) {
            SLOG_E("screen_set_window_property_iv for SCREEN_PROPERTY_USAGE failed, error:%s", strerror(errno));
            return error;
        }
        // create screen window buffers
        error = screen_create_window_buffers(win_, 1);
        if (error) {
            SLOG_E("screen_create_window_buffers failed, error:%s", strerror(errno));
            return error;
        }
        SLOG_I("qnx screen display init win ok!");
        return 0;
    }
    void unit_win() {
        screen_destroy_window(win_);
    }
public:
    inline void set_display_zorder(int zorder) {
        display_zorder_ = zorder;
    }
};