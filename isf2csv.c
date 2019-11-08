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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "isf2csv.h"

float isf2csv(uint16_t sample)
{
	(void)sample;
	return 0.0f;
}

#ifndef ISF2CSV_NOMAIN
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("%s ISF\n", argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
#endif
