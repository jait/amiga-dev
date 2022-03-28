/* vim: ts=4 sts=4 sw=4 noet: 
*/
#if 0
#include <stdio.h>
#include <math.h>
#include <libraries/mathffp.h>
#endif
#include "precalc.h"

#define PI 3.1415927

static WORD sintable[180] = {
	0,    17,  35,  52,  70,  87, 105, 122, 139, 156, 
	174, 191, 208, 225, 242, 259, 276, 292, 309, 326,
	342, 358, 375, 391, 407, 423, 438, 454, 469, 485, 
	500, 515, 530, 545, 559, 574, 588, 602, 616, 629, 
	643, 656, 669, 682, 695, 707, 719, 731, 743, 755, 
	766, 777, 788, 799, 809, 819, 829, 839, 848, 857,
	866, 875, 883, 891, 899, 906, 914, 921, 927, 934,
	940, 946, 951, 956, 961, 966, 970, 974, 978, 982,
	985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,
	1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 
	985, 982, 978, 974, 970, 966, 961, 956, 951, 946, 
	940, 934, 927, 921, 914, 906, 899, 891, 883, 875, 
	866, 857, 848, 839, 829, 819, 809, 799, 788, 777, 
	766, 755, 743, 731, 719, 707, 695, 682, 669, 656, 
	643, 629, 616, 602, 588, 574, 559, 545, 530, 515, 
	500, 485, 469, 454, 438, 423, 407, 391, 375, 358, 
	342, 326, 309, 292, 276, 259, 242, 225, 208, 191,
	174, 156, 139, 122, 105, 87,  70,  52,  35,  17
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
	if (deg >= 180) {
		return -1 * sintable[(deg % 360) - 180];
	}
	else {
		return sintable[deg];
	}
}
