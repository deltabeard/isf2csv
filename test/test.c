#include <stdint.h>

#include "minctest.h"
#include "../isf2csv.h"

void t_wav_check(void)
{
	uint16_t wave[] = {
		0x0e00, 0x0a00, 0x0700, 0x0200,
		0xff00, 0xfa00, 0xf700, 0xf400
	};

	float expected[] = {
		0.5600, 0.4000, 0.2800, 0.0800,
		-0.0400, -0.2400, -0.3600, -0.4800
	};

	for(uint_fast32_t i = 0; i < sizeof(wave)/sizeof(*wave); i++)
		lfequal(isf2csv(wave[i]), expected[i]);
}

int main(void)
{
	lrun("Waveform check", t_wav_check);
	lresults();
	return lfails != 0;
}
