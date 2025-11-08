// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2025

#include <wonderful.h>
#include <sys/bios.h>

void main(void) {
	text_screen_init();

	while(1) {
		sys_wait(1);

		for (int i = 0; i < 18; i++) {
			text_put_numeric(0, i, 4, NUM_HEXA | NUM_PADZERO, key_press_check());
			text_put_numeric(5, i, 4, NUM_HEXA | NUM_PADZERO, key_hit_check());
		}
	}
}
