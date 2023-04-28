#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <screen/screen.h>
#include "qnx_slog2.hpp"
struct qnx_screen_context {
    screen_context_t screen_ctx;
    screen_display_t *screen_disps = nullptr;
    int screen_size[2] = { 0 };
    qnx_screen_context() = default;
    virtual ~qnx_screen_context() {
        uninit();
        memset(screen_size, 0, sizeof(screen_size));
    }
    int init() {
        int display_count = 0;
        int res = screen_create_context(&screen_ctx, SCREEN_APPLICATION_CONTEXT);
        if (res) {
            SLOG_E("screen_create_context failed:%s", strerror(errno));
            return res;
        }
        // Using the number of displays returned by the query,
        // allocate enough memory to retrieve an array of pointers to screen_display_t
        res = screen_get_context_property_iv(screen_ctx, SCREEN_PROPERTY_DISPLAY_COUNT, &display_count);
        if (res) {
            SLOG_E("screen_get_context_property_iv failed:%s", strerror(errno));
            return res;
        }
        SLOG_I("qnx get screen count:%d", display_count);
        if (display_count < 2) {
            SLOG_E("SCREEN_PROPERTY_DISPLAY_COUNT is less than 2!");
            res = -111;
            return res;
        }
        screen_disps = (screen_display_t *)calloc(display_count, sizeof(screen_display_t));
        assert(screen_disps != nullptr);
        res = screen_get_context_property_pv(screen_ctx, SCREEN_PROPERTY_DISPLAYS, (void **)screen_disps);
        if (res) {
            SLOG_E("screen_get_context_property_pv failed:%s", strerror(errno));
            return res;
        }
        // Must be 1, otherwise it cannot be drawn
        screen_display_t screen_disp = screen_disps[1];
        res = screen_get_display_property_iv(screen_disp, SCREEN_PROPERTY_SIZE, screen_size);
        if (res) {
            SLOG_E("screen_get_display_property_iv failed:%s", strerror(errno));
            return res;
        }
        SLOG_I("qnx_screen_context get screen size:%dx%d", screen_size[0], screen_size[1]);
        return 0;
    }
private:
    void uninit() {
        screen_destroy_context(screen_ctx);
        if (screen_disps != nullptr) {
            free(screen_disps);
            screen_disps = nullptr;
        }
    }

};
