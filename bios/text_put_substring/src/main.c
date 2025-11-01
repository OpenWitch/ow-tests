// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2025

#include <wonderful.h>
#include <sys/bios.h>

static const char __wf_rom text_mode_str0[] = "   ASCII   ";
static const char __wf_rom text_mode_str1[] = "ASCII/シフトジス";
static const char __wf_rom text_mode_str2[] = "   シフトジス   ";
static const char __wf_rom* __wf_rom text_mode_str[] = {
	text_mode_str0,
	text_mode_str1,
	text_mode_str2
};

const char str1[] = "text_put_substring fail";
const char str2[] = "this is a very long string which should probably wrap around\nno newline\0failure";

void main(void) {
	int curr_mode = 0;

	while(1) {
		screen_fill_char(0, 0, 0, 28, 18, 0);
		text_set_mode(curr_mode % 3);
		text_screen_init();
		text_window_init(1, 1, 24, 16, 16);
		text_put_string(
			(24 - 11) >> 1,
			15,
			text_mode_str[curr_mode]
		);

		if (curr_mode >= 3) {
			for (int i = 64; i < 126; i++) {
				text_put_char(i - 64, 0, i);
			}
		} else {
			text_put_substring(0, 0, str1, 18);
			text_put_substring(0, 1, str2, 65535);
			text_put_char(26, 0, 'O');
			text_put_char(26+32, 0, 'u');
			text_put_char(26+32*2, 0, 't');
		}

		while (true) {
			uint16_t k = key_wait();
			if (k == KEY_A) break;
			if (k == KEY_B) return;
		}

		curr_mode = (curr_mode + 1) % 6;
	}
}
