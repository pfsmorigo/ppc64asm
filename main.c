#include <stdio.h>
#include "ppc64asm.h"

void load_register_example() {
	lis(7, 0xaabb);
	ori(7, 7, 0xccdd);
	rldicr(7, 7, 32, 31);
	oris(7, 7, 0xeeff);
	ori(7, 7, 0x1122);
	show_table();
}

void invert_value_in_vector_example() {
	r[4] = 0x3fffffffeca8;
	v(9, 0x1100ffeeddccbbaa, 0x9988776655443322);

	show_table();
	neg(7, 4);
	lvsr(5, 0, 7);
	vspltisb(6, 15);
	vxor(5, 5, 6);
	vperm(9, 9, 9, 5);
	show_table();
}

void set_encrypt_key() {
	neg(9, 3);
	lvx(1, 0, 3);
	addi(3, 3, 15);
	lvsr(3, 0, 9);
	li(8, 0x20);
	cmpwi(4, 192);
	lvx(2, 0, 3);
	vspltisb(5, 0x0f);
	lvx(4, 0, 6);
	vxor(3, 3, 5);
	lvx(5, 8, 6);
	addi(6, 6, 0x10);
	vperm(1, 1, 2, 3);
	li(7, 8);
	vxor(0, 0, 0);
	mtctr(7);
}

int main(int argc, char **argv)
{
	/*load_register_example();*/
	/*invert_value_in_vector_example();*/
	set_encrypt_key();

	return 0;
}
