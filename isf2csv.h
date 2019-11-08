#include <stdint.h>

enum encoding_e {
	ENC_UNKNOWN, ENC_ASCII, ENC_BINARY
};

struct header_s {
	uint_fast32_t points;

	/* Number of bytes per sample. */
	uint_fast8_t width;
	enum encoding_e enc;
	char* info_str;

	/* Value to multiple data point by to get sample. */
	double ymult;
	/* Y-Axis offset. */
	double yzero;
};

double isf2csv(const int16_t sample, const double ymult, const double yzero);
uint_fast16_t get_header_length(const char *buf);
struct header_s get_header(const char *str, uint_fast16_t len);
