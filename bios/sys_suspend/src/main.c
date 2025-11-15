// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2024

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <wonderful.h>
#include <sys/bios.h>

// This test is very messy. FIXME?

#define _heap ((uint8_t*) (*((uint16_t*) 0x005E)))

bool flag = false;

void main(void) {
	int y = 0;

	sys_set_resume(0x4000);
	text_screen_init();
	text_put_string(0, y, "sys_get_resume = ");
	text_put_numeric(28 - 4, y++, 4, NUM_HEXA | NUM_PADZERO, sys_get_resume());

	// free all SRAM memory from heap onwards
	text_put_string(0, y, "heap = ");
	text_put_numeric(7, y++, 4, NUM_HEXA | NUM_PADZERO, (uint16_t) _heap);
	memset(_heap, 0, -((uint16_t) _heap));

	text_put_string(0, y++, "suspend 0 spr = 55AA55AA");
	outportw(0x0C, 0xAA55);
	outportw(0x0E, 0xAA55);
	sys_suspend(0);

	text_put_string(0, y++, "suspend 0 again");

	if (sys_suspend(0) == 0) {
		text_put_numeric(28 - 4, y, 4, NUM_HEXA | NUM_PADZERO, sys_get_resume());
		text_put_string(0, y++, "trying to resume");
		sys_wait(75);
		sys_resume(0);
		while(1);
	} else {
		text_put_numeric(28 - 4, y, 4, NUM_HEXA | NUM_PADZERO, sys_get_resume());
		text_put_string(0, y++, "resuming");
	}

	text_put_string(0, y++, "suspend 1 spr = AA55AA55");
	outportw(0x0C, 0x55AA);
	outportw(0x0E, 0x55AA);

	if (sys_suspend(1) == 0) {
		text_put_numeric(28 - 4, y, 4, NUM_HEXA | NUM_PADZERO, sys_get_resume());
		text_put_string(0, y++, "trying to resume");
		sys_wait(75);
		sys_resume(1);
		while(1);
	} else {
		text_put_numeric(28 - 4, y, 4, NUM_HEXA | NUM_PADZERO, sys_get_resume());
		text_put_string(0, y++, "resuming");
		if (!flag) {
			flag = true;
			text_put_string(0, y++, "trying to resume again");
			sys_wait(75);
			sys_resume(1);
		}
	}

	text_put_string(0, y, "sys_set_resume FFFF");
	sys_set_resume(0xFFFF);
	text_put_numeric(28 - 4, y++, 4, NUM_HEXA | NUM_PADZERO, sys_get_resume());
	text_put_string(0, y, "sys_set_resume 0000");
	sys_set_resume(0x0000);
	text_put_numeric(28 - 4, y++, 4, NUM_HEXA | NUM_PADZERO, sys_get_resume());

	text_put_string(0, 11, "Press B to exit...");
	while(key_wait() != KEY_B);
}
