#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/bios.h>

void draw_pass_fail(int y, int mx, bool success) {
    int x = 27 - mx;
    text_put_char(x, y, success ? 'O' : 'X');
}

void main(void) {
    static char buf[32];

    text_screen_init();

    int i = 0;
    uint8_t *ptr1 = malloc(64);
    sprintf(buf, "malloc 64 = %04X", ptr1);
    text_put_string(0, i, buf);

    i++;
    uint8_t *ptr2 = malloc(128);
    sprintf(buf, "malloc 128 = %04X", ptr2);
    text_put_string(0, i, buf);
    i++;
    uint8_t *ptr3 = malloc(256);
    sprintf(buf, "malloc 256 = %04X", ptr3);
    text_put_string(0, i, buf);
    i++;

    memset(ptr1, 1, 64);
    memset(ptr2, 2, 128);
    memset(ptr3, 3, 256);
    draw_pass_fail(i - 2, 1, ptr3[255] == 3);
    draw_pass_fail(i - 2, 0, ptr3[0] == 3);
    draw_pass_fail(i - 3, 1, ptr2[0] == 2);
    draw_pass_fail(i - 3, 0, ptr2[127] == 2);
    draw_pass_fail(i - 4, 1, ptr1[0] == 1);
    draw_pass_fail(i - 4, 0, ptr1[63] == 1);

    free(ptr1);
    sprintf(buf, "free 64");
    text_put_string(0, i, buf);
    i++;
    uint8_t *ptr5 = malloc(62);
    uint8_t *ptr6 = malloc(2);
    sprintf(buf, "malloc 62 = %04X", ptr5);
    text_put_string(0, i, buf);
    i++;
    sprintf(buf, "malloc 2 = %04X", ptr6);
    text_put_string(0, i, buf);
    i++;
    free(ptr2);
    sprintf(buf, "free 128");
    text_put_string(0, i, buf);
    i++;
    uint8_t *ptr7 = malloc(66);
    uint8_t *ptr8 = malloc(60);
    sprintf(buf, "malloc 66 = %04X", ptr7);
    text_put_string(0, i, buf);
    i++;
    sprintf(buf, "malloc 60 = %04X", ptr8);
    text_put_string(0, i, buf);
    i++;

    free(ptr8);
    sprintf(buf, "free 60");
    text_put_string(0, i, buf);
    i++;
    ptr7 = realloc(ptr7, 62);
    sprintf(buf, "realloc 66->62 = %04X", ptr7);
    text_put_string(0, i, buf);
    i++;
    ptr7 = realloc(ptr7, 90);
    sprintf(buf, "realloc 62->90 = %04X", ptr7);
    text_put_string(0, i, buf);
    i++;
    ptr7 = realloc(ptr7, 480);
    sprintf(buf, "realloc 90->480 = %04X", ptr7);
    text_put_string(0, i, buf);
    i++;

    while(key_wait() != KEY_B);
}
