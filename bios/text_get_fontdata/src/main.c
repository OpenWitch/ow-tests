// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2024

#include <string.h>
#include <wonderful.h>
#include <ws.h>
#include <sys/bios.h>

static const char __wf_rom mode[] = "mode ";
static const char __wf_rom ascii[] = "ascii: ";
static const char __wf_rom sjis[] = "s-jis: ";
static const char __wf_rom unkn[] = "unkn.: ";
uint8_t buffer[16];

__attribute__((noinline))
uint16_t text_get_fontdata_with_result(uint16_t ch, void __far* data) {
	uint16_t result;
	__asm volatile (
		"int $0x13"
		: "=a" (result)
		: "Rds" (FP_SEG(data)), "d" (FP_OFF(data)), "c" (ch), "Rah" ((uint8_t) 0x0D)
		: "cc", "memory"
	);
	return result;
}

void main(void) {
	uint16_t result[3][3];
	for (int i = 0; i < 3; i++) {
		text_set_mode(i);
		result[i][0] = text_get_fontdata_with_result(0x0040, buffer);
		result[i][1] = text_get_fontdata_with_result(0x824f, buffer);
		result[i][2] = text_get_fontdata_with_result(0xf6de, buffer);
	}

	text_set_mode(1);
	text_screen_init();
	for (int i = 0; i < 3; i++) {
		text_put_string(0, i*5+0, mode);
		text_put_string(0, i*5+1, ascii);
		text_put_string(0, i*5+2, sjis);
		text_put_string(0, i*5+3, unkn);
		text_put_numeric(5, i*5+0, 4, NUM_ALIGN_LEFT, i);
		text_put_numeric(7, i*5+1, 4, NUM_HEXA | NUM_PADZERO, result[i][0]);
		text_put_numeric(7, i*5+2, 4, NUM_HEXA | NUM_PADZERO, result[i][1]);
		text_put_numeric(7, i*5+3, 4, NUM_HEXA | NUM_PADZERO, result[i][2]);
	}

	key_wait();
}

