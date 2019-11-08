/**
 * isf2csv
 * Converts ISF waveform files to CSV
 * Copyright (C) 2019  Mahyar Koshkouei
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "isf2csv.h"

double isf2csv(const int16_t sample, const double ymult, const double yzero)
{
	double ret = ((int16_t)__builtin_bswap16(sample) * ymult) + yzero;
	return ret;
}

uint_fast16_t get_header_length(const char *buf)
{
	/* Get length of header. */
	char *loc;
	char offset_str[] = "0";
	char needle[] = ":CURVE #";
	int offset = 0;
	uint_fast16_t len;

	loc = strstr(buf, needle);
	assert(loc != NULL);

	loc += strlen(needle);
	*offset_str = *loc;
	offset = atoi(offset_str);
	assert(offset > 0);

	loc += offset + strlen(offset_str);
	len = loc - buf;

	return len;
}

struct header_s get_header(const char *str, uint_fast16_t len)
{
	struct header_s h = {
		.points = 0,
		.width = 0,
		.enc = ENC_UNKNOWN,
		.info_str = "EMPTY",
		.ymult = 0,
		.yzero = 0
	};

	/* YMULT */
	{
		const char needle[] = "YMULT ";
		char *loc;
		char *endptr;

		loc = strstr(str, needle);
		assert(loc != NULL);
		loc += strlen(needle);

		h.ymult = strtod(loc, &endptr);
		assert(endptr[0] == ';');
	}

	/* YZERO */
	{
		const char needle[] = "YZERO ";
		char *loc;
		char *endptr;

		loc = strstr(str, needle);
		assert(loc != NULL);
		loc += strlen(needle);

		h.yzero = strtod(loc, &endptr);
		assert(endptr[0] == ';');
	}

	return h;
}

#ifndef ISF2CSV_NOMAIN
int main(int argc, char *argv[])
{
	FILE *f;

	if(argc != 2)
	{
		printf("%s ISF\n", argv[0]);
		return EXIT_FAILURE;
	}

	f = fopen(argv[1], "rb");
	if(f == NULL)
	{
		perror("Cannot open ISF file");
		return EXIT_FAILURE;
	}
	
	char buf[512];
	fread(buf, sizeof(buf), 1, f);
	buf[511] = '\0';

	const uint_fast16_t h_len = get_header_length(buf);
	struct header_s h = get_header(buf, h_len);
	
	fseek(f, h_len, SEEK_SET);
	uint16_t bin[2048];
	size_t elem = fread(bin, sizeof(uint16_t), sizeof(bin)/sizeof(*bin), f);

	do {
		for(size_t i = 0; i < elem; i++)
			printf("%g\n", isf2csv(bin[i], h.ymult, h.yzero));

		elem = fread(bin, sizeof(uint16_t), sizeof(bin)/sizeof(*bin), f);
	} while(elem != 0);

	fclose(f);

	return EXIT_SUCCESS;
}
#endif
