#include <stdio.h>
#include "pwrasm.h"

int main(int argc, char **argv)
{
	r[4] = 0x3fffffffeca8;
	v(9, 0x1100ffeeddccbbaa, 0x9988776655443322);

	show_table();
	neg(7, 4);
	lvsr(5, 0, 7);
	vspltisb(6, 15);
	vxor(5, 5, 6);
	vperm(9, 9, 9, 5);
	show_table();

	return 0;
}
