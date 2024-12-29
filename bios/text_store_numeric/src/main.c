// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2024

#include <wonderful.h>
#include <sys/bios.h>

const char str_header[] = "text_store_numeric test:";
char buffer[64];

void main(void) {
	uint16_t len;
	text_screen_init();

	text_put_string(0, 0, str_header);
	for (int i = 0; i < 16; i++) {
		len = text_store_numeric(buffer, 8, i, 1234);
		text_put_substring(0, i+2, buffer, len);
		len = text_store_numeric(buffer, 8, i, -2345);
		text_put_substring(9, i+2, buffer, len);
		len = text_store_numeric(buffer, 0, i, 3456);
		text_put_substring(18, i+2, buffer, len);
	}

	while(key_wait() != KEY_B);
}
