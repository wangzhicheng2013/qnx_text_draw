#include "qnx_text_draw.hpp"
#include "qnx_screen_display.hpp"
int main() {
    if (false == SLOG_INIT()) {
        return -1;
    }
    qnx_text_draw text_draw(100, 100, 36);
    int ret = text_draw.init();
    if (ret) {
        printf("text draw init error:%d\n", ret);
        return -1;
    }
    const wchar_t *chinese_str = L"樊";
    printf("draw result:%d\n", text_draw.draw(chinese_str));

    qnx_screen_context screen_ctx;
    ret = screen_ctx.init();
    printf("screen_ctx init:%d\n", ret);

    return 0;
}