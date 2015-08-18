#include <stdio.h>
#include "pwrasm.h"

void load_register_example() {
	lis(7, 0xaabb);
	ori(7, 7, 0xccdd);
	rldicr(7, 7, 32, 31);
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
	load_register_example();
	/*invert_value_in_vector_example();*/
	/*show_table();*/
	return 0;
}
