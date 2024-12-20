// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2024

#include <stdbool.h>
#include <stdint.h>
#include <wonderful.h>
#include <sys/bios.h>

typedef struct xmodem_info {
	uint16_t state;
	uint8_t mode;
	uint8_t retry_count;
	uint16_t block_count;
	uint16_t block_max;
	uint16_t block_size;
	uint16_t bank;
	uint16_t offset;
	uint16_t timeout_count;
} __attribute__((packed)) xmodem_info_t;

int selected_field = 0;
int selected_component = 0;
xmodem_info_t xminfo;
uint16_t xmret = 0;

const char int_to_hex[] = "0123456789ABCDEF";
void edit_field(void *value, int field, int width, uint16_t pressed) {
	uint8_t *v8 = (uint8_t *) value;
	uint16_t *v16 = (uint16_t *) value;
	int shift = (width - 1) * 4;

	if (selected_field == field) {
		if (selected_component >= width) {
			selected_component = (pressed & KEY_RIGHT1) ? 0 : (width - 1);
		} else if (selected_component < 0) {
			selected_component = (pressed & KEY_LEFT1)  ? (width - 1) : 0;
		}

 		if (pressed) {
			int cshift = (shift - selected_component * 4);
			int c = ((*v16) >> cshift) & 0xF;
			if (pressed & KEY_LEFT2) {
				c = (c - 1) & 0x0F;
			}
			if (pressed & KEY_RIGHT2) {
				c = (c + 1) & 0x0F;
			}
			if (pressed & KEY_DOWN2) {
				c = (c - 4) & 0x0F;
			}
			if (pressed & KEY_UP2) {
				c = (c + 4) & 0x0F;
			}
			if (width == 2) {
				*v8 = ((*v8) & ~(0xF << cshift)) | (c << cshift);
			} else {
				*v16 = ((*v16) & ~(0xF << cshift)) | (c << cshift);
			}
		}
	}

	for (int i = 0; i < width; i++) {
		char c = int_to_hex[((*v16) >> (shift - i * 4)) & 0xF];
		if (selected_component == i && selected_field == field) {
			text_set_palette(1);
			text_put_char(1 + i, 1 + field, c);
			text_set_palette(0);
		} else {
			text_put_char(1 + i, 1 + field, c);
		}
	}
}

void main(void) {
	comm_set_timeout(65535, 65535);
	comm_set_cancel_key(KEY_B);

	comm_open();

	text_screen_init();
	text_put_string(6, 1, "state");
	text_put_string(6, 2, "mode");
	text_put_string(6, 3, "retry count");
	text_put_string(6, 4, "block count");
	text_put_string(6, 5, "block max");
	text_put_string(6, 6, "block size");
	text_put_string(6, 7, "bank");
	text_put_string(6, 8, "offset");
	text_put_string(6, 9, "timeout #");

	xminfo.state = 1;

	while (true) {
		sys_wait(1);
		int pressed = key_hit_check_with_repeat();

		if (pressed & KEY_UP1) {
			selected_field = selected_field - 1;
			if (selected_field < 0) selected_field = 8;
		}
		if (pressed & KEY_DOWN1) {
			selected_field = selected_field + 1;
			if (selected_field > 8) selected_field = 0;
		}
		if (pressed & KEY_LEFT1) {
			selected_component = selected_component - 1;
		}
		if (pressed & KEY_RIGHT1) {
			selected_component = selected_component + 1;
		}

		edit_field((void*) &xminfo.state, 0, 4, pressed);
		edit_field((void*) &xminfo.mode, 1, 2, pressed);
		edit_field((void*) &xminfo.retry_count, 2, 2, pressed);
		edit_field((void*) &xminfo.block_count, 3, 4, pressed);
		edit_field((void*) &xminfo.block_max, 4, 4, pressed);
		edit_field((void*) &xminfo.block_size, 5, 4, pressed);
		edit_field((void*) &xminfo.bank, 6, 4, pressed);
		edit_field((void*) &xminfo.offset, 7, 4, pressed);
		edit_field((void*) &xminfo.timeout_count, 8, 4, pressed);
		edit_field((void*) &xmret, 9, 4, pressed);

		if (pressed & KEY_A) {
		        __asm volatile (
        		        "int $0x14"
	        	        : "=a" (xmret)
                		: "Rds" (FP_SEG(&xminfo)), "b" (FP_OFF(&xminfo)), "Rah" ((uint8_t) 0x0D)
	        	        : "cc", "memory"
		        );
		}
		if (pressed & KEY_START) {
			break;
		}
	}

	comm_close();
}
