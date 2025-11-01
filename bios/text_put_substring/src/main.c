// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2025

#include <wonderful.h>
#include <sys/bios.h>

const char str1[] = "text_put_substring fail";
const char str2[] = "this is a very long string which should probably wrap around\nno newline\0failure";

void main(void) {
	text_screen_init();
	text_window_init(1, 1, 26, 16, 16);
	text_put_substring(0, 0, str1, 18);
	text_put_substring(0, 1, str2, 65535);
	while(key_wait() != KEY_B);
}
