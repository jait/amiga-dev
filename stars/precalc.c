/* vim: ts=4 sts=4 sw=4 noet: 
*/
#if 0
#include <stdio.h>
#include <math.h>
#include <libraries/mathffp.h>
#endif
#include "precalc.h"

#define PI 3.1415926536

/* sin(deg) * 16384 */
static UWORD sintable[91] = {
	0, 286, 572, 857, 1143, 1428, 1713, 1997, 2280, 2563,
	2845, 3126, 3406, 3686, 3964, 4240, 4516, 4790, 5063, 5334,
	5604, 5872, 6138, 6402, 6664, 6924, 7182, 7438, 7692, 7943,
	8192, 8438, 8682, 8923, 9162, 9397, 9630, 9860, 10087, 10311,
	10531, 10749, 10963, 11174, 11381, 11585, 11786, 11982, 12176, 12365,
	12551, 12733, 12911, 13085, 13255, 13421, 13583, 13741, 13894, 14044,
	14189, 14330, 14466, 14598, 14726, 14849, 14968, 15082, 15191, 15296,
	15396, 15491, 15582, 15668, 15749, 15826, 15897, 15964, 16026, 16083,
	16135, 16182, 16225, 16262, 16294, 16322, 16344, 16362, 16374, 16382,
	16384
};


void initPreCalc() {
	/*
	for (UBYTE i = 0; i < 180; i++) {
		sintable[i] = SPSin(i * PI / 180.0) * 1000.0;
		sintable[i] = round(sin(i * PI / 180.0) * 1000.0); 
		printf("sin %d (rad %d) = %d\n", i, i * PI / 180.0 * 1000.0, sintable[i]);
	}
	*/
	return;
}

WORD pcSin(UWORD deg) {
	BOOL neg = FALSE;
	if (deg > 180) {
		deg = (deg % 360) - 180;
		neg = TRUE;
	}
	if (deg > 90) {
		deg = 180 - deg;
	}
	if (neg) {
		return -1 * sintable[deg];
	}
	else {
		return sintable[deg];
	}
}

