#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define REFERENCE(x) printf(x)

void vperm(uint64_t vrt, uint64_t vra, uint64_t vrb, uint64_t vrc) {
	REFERENCE("Vector Permute VA-form | VRT,VRA,VRB,VRC | P. 198\n");
}

int main(int argc, char **argv)
{
	uint64_t vr5 = 0x08090a0b0c0d0e0f1011121314151617;
	uint64_t vr9 = 0x07060504030201001f1e1d1c1b1a1918;

	vperm(vr9, vr9, vr9, vr5);

	return 0;
}
