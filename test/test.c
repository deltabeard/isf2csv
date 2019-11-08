#include <stdint.h>

#include "minctest.h"
#include "../isf2csv.h"

const char str[] = ":WFMPRE:NR_PT 20000000;:WFMPRE:BYT_NR 2;BIT_NR 16;ENCDG BINARY;BN_FMT RI;BYT_OR MSB;WFID \"Ch1, DC coupling, 1.000V/div, 800.0us/div, 20000000 points, Sample mode\";NR_PT 20000000;PT_FMT Y;XUNIT \"s\";XINCR 400.0000E-12;XZERO 0.0E+0;PT_OFF 0;YUNIT \"V\";YMULT 156.2500E-6;YOFF 0.0E+0;YZERO 0.0E+0;VSCALE 1.0000;HSCALE 800.0000E-6;VPOS 0.0E+0;VOFFSET 0.0E+0;HDELAY 4.0000E-3;DOMAIN TIME;WFMTYPE ANALOG;CENTERFREQUENCY 0.0E+0;SPAN 0.0E+0;REFLEVEL 0.0E+0;:CURVE #840000000GARBAGEDATA";

void t_wav_check(void)
{
	uint16_t wave[] = {
		0x0e00, 0x0a00, 0x0700, 0x0200,
		0xff00, 0xfa00, 0xf700, 0xf400
	};

	double ymult = 156.25e-6;

	double expected[] = {
		0.5600, 0.4000, 0.2800, 0.0800,
		-0.0400, -0.2400, -0.3600, -0.4800
	};

	for(uint_fast32_t i = 0; i < sizeof(wave)/sizeof(*wave); i++)
		lfequal(isf2csv(wave[i], ymult, 0.0f), expected[i]);
}

void t_hl_check(void)
{
	uint_fast16_t len = get_header_length(str);

	lequal(len, 463);
}

void t_hl_fill(void)
{
	const uint_fast16_t len = get_header_length(str);
	struct header_s h = get_header(str, len);

	lequal(h.points, 20000000);
	lequal(h.width, 2);
	lequal(h.enc, ENC_BINARY);
	lok(strcmp(h.info_str,
				"Ch1, DC coupling, 1.000V/div, 800.0us/div, "
				"20000000 points, Sample mode") == 0);
	lfequal(h.ymult, 156.2500e-6);
	lfequal(h.yzero, 0.0f);
}

int main(void)
{
	lrun("Waveform check", t_wav_check);
	lrun("Header len", t_hl_check);
	lrun("Header fill", t_hl_fill);
	lresults();
	return lfails != 0;
}
