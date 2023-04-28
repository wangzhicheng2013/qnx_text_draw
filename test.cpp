#include "qnx_text_draw.hpp"
int main() {
    qnx_text_draw text_draw(100, 100, 36);
    int ret = text_draw.init();
    if (ret) {
        printf("text draw init error:%d\n", ret);
        return -1;
    }
    const wchar_t *chinese_str = L"樊";
    printf("draw result:%d\n", text_draw.draw(chinese_str));

    return 0;
}