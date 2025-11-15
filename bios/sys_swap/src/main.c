// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2024

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <wonderful.h>
#include <sys/bios.h>

void main(void) {
	int y = 0;

	text_screen_init();
	text_put_string(0, y++, "sys_suspend(0)");
	sys_wait(75);
	if (sys_suspend(0) == 0) {
		text_put_string(0, y++, "sys_swap(0)");
		sys_wait(75);
		if (sys_swap(0) == 0) {
			text_put_string(0, y++, "sys_resume(0)");
			sys_wait(75);
			sys_resume(0);
		} else {
			text_put_string(0, y++, "return from sys_swap(0)");
		}
	} else {
		text_put_string(0, y++, "return from sys_suspend(0)");
	}

	text_put_string(0, ++y, "Press B to exit...");
	while(key_wait() != KEY_B);
}
