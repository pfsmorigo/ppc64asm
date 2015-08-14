#include <stdio.h>
#include "pwrasm.h"

int main(int argc, char **argv)
{
	r[4] = 0x3fffffffeca8;
	v(9, 0x1100ffeeddccbbaa, 0x9988776655443322);

	v_str(9);
	printf("%s | vr%u\n", vector_str, 9);
	printf("\n");

	neg(7, 4);
	lvsr(5, 0, 7);
	vspltisb(6, 15);
	vxor(5, 5, 6);
	vperm(9, 9, 9, 5);

	return 0;
}
