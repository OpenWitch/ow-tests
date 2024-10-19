// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Adrian "asie" Siekierka, 2024

#include <wonderful.h>
#include <sys/bios.h>

uint8_t i = 0;
datetime_t date;

const char *dow_string[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

void main(void) {
	text_screen_init();
	text_put_string(2, 1, "RTC date/time (get):");
	text_put_string(2, 3, "....-..-..");
	text_put_string(2, 4, "..:..:..");

	text_put_numeric(2, 3, 4, NUM_PADZERO, rtc_get_year() + 2000);
	text_put_numeric(7, 3, 2, NUM_PADZERO, rtc_get_month());
	text_put_numeric(10, 3, 2, NUM_PADZERO, rtc_get_date());

	text_put_string(13, 3, dow_string[rtc_get_day_of_week()]);

	text_put_numeric(2, 4, 2, NUM_PADZERO, rtc_get_hour());
	text_put_numeric(5, 4, 2, NUM_PADZERO, rtc_get_minute());
	text_put_numeric(8, 4, 2, NUM_PADZERO, rtc_get_second());

	while(key_wait() != KEY_B);

	text_put_string(2, 1, "RTC date/time (struct):");
	text_put_string(2, 3, "....-..-..");
	text_put_string(2, 4, "..:..:..");

	rtc_get_datetime_struct(&date);
	text_put_numeric(2, 3, 4, NUM_PADZERO, date.year + 2000);
	text_put_numeric(7, 3, 2, NUM_PADZERO, date.month);
	text_put_numeric(10, 3, 2, NUM_PADZERO, date.date);

	text_put_string(13, 3, dow_string[date.day_of_week]);

	text_put_numeric(2, 4, 2, NUM_PADZERO, date.hour);
	text_put_numeric(5, 4, 2, NUM_PADZERO, date.minute);
	text_put_numeric(8, 4, 2, NUM_PADZERO, date.second);

	while(key_wait() != KEY_B);
}
