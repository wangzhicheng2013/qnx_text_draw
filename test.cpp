#include "qnx_text_draw.hpp"
#include "qnx_screen_display_zone.hpp"
#include "qnx_screen_display_image.hpp"
#include <fcntl.h>
int main(int argc, const char **argv) {
    if (false == SLOG_INIT()) {
        return -1;
    }
    /*qnx_text_draw text_draw(100, 100, 36);
    int error = text_draw.init();
    if (error) {
        printf("text draw init error:%d\n", error);
        errorurn -1;
    }
    const wchar_t *chinese_str = L"樊";
    printf("draw result:%d\n", text_draw.draw(chinese_str));
    */
    int error = QNX_SCREEN_CTX.init();
    if (error) {
        SLOG_E("qnx screen context init failed:%d", error);
        return -2;
    }
    error = QNX_SCREEN_DISPLAY_ZONE.init();
    if (error) {
        SLOG_E("qnx screen display zone init failed:%d", error);
        return -3;
    }
    // test black the screen
    QNX_SCREEN_DISPLAY_ZONE.set_display_margin(0, 0, 100, 100);
    sleep(10);
    error = QNX_SCREEN_DISPLAY_IMAGE.init();
    if (error) {
        SLOG_E("qnx screen display image init failed:%d", error);
        return -4;
    }
    // test display image
    FILE *fp = fopen("./123.uyvy", "rb");
    if (!fp) {
        printf("can not open ./123.uyvy!\n");
        return -5;
    }
    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *uyvy_content = (char *)malloc(sizeof(char) * file_size);
    assert(uyvy_content != nullptr);
    fread(uyvy_content, 1, file_size, fp);
    fclose(fp);
    QNX_SCREEN_DISPLAY_IMAGE.set_display_position(0, 0);
    QNX_SCREEN_DISPLAY_IMAGE.set_image_size(1920, 1080);
    QNX_SCREEN_DISPLAY_IMAGE.set_display_size(1920, 1080);
    QNX_SCREEN_DISPLAY_IMAGE.display_image(uyvy_content);
    sleep(10);
    free(uyvy_content);

    return 0;
}