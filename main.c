#include <stdio.h>
#include "pwrasm.h"

/*#define MASK3(x, y) ~((~ 0ULL) >> (sizeof(0ULL)*8-y)) << x*/

/*#define MASK3(x, y) ~((~ 0ULL) >> (sizeof(0ULL)*8-y))*/
#define MASK3(x, y) ((~ 0ULL) << x >> y)

void load_register_example() {
	lis(7, 0xaabb);
	ori(7, 7, 0xccdd);
	rldicr(7, 7, 32, 32);
	/*oris(7, 7, 0xeeff);*/
	/*ori(7, 7, 0x0011);*/
}

void invert_value_in_vector_example() {
	v(9, 0x1100ffeeddccbbaa, 0x9988776655443322);
	addi(4, 0, 0x3fffffffeca8);
	neg(7, 4);
	lvsr(5, 0, 7);
	vspltisb(6, 15);
	vxor(5, 5, 6);
	vperm(9, 9, 9, 5);
	show_table();
}

int main(int argc, char **argv)
{
	printf("%s\n", binary_str(generic_buffer, (uint8_t) (~0) >> 0, 64));

	/*invert_value_in_vector_example();*/
	/*load_register_example();*/
	/*show_table();*/
	return 0;
}
