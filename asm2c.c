#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h> // for PRIx64

#define REFERENCE(x) printf(x)
#define HEX "%32llx"

uint64_t r[32];
uint64_t vr[32][2];
uint8_t vector_str[sizeof("11223344556677889900112233445566")];

void *v_str(uint8_t vector_num) {
	sprintf(vector_str, "%16llx%016llx", vr[vector_num][1],
			                                    vr[vector_num][0]);
}

void v(uint8_t vector_num, uint64_t high, uint64_t low) {
	vr[vector_num][0] = low;
	vr[vector_num][1] = high;
}

void neg(uint8_t t, uint8_t a) {
	REFERENCE("Negate | XO-form | RT,RA | P. 70\n");

	printf("\n");
	printf("---- neg(RT, RA)\n");
	printf("         %2u  %2u\n", t, a);
	printf("\n");
	printf(HEX"| RA\n", r[a]);
	printf(HEX"| ~RA\n", ~(r[a]));
	printf(HEX"| ~RA + 1 = RT\n", ~(r[a]) + 1);
	printf("\n");

	r[t] = ~(r[a]) + 1;
}

void lvsr(uint8_t *vtr, uint64_t *ra, uint64_t *rb) {
	REFERENCE("Load Vector for Shift Right: VTR,RA,RB\n");

	printf("\n");
	printf(HEX"| RA\n", *ra);
	printf(HEX"| RB\n", *rb);
	printf("\n");
}


int main(int argc, char **argv)
{
	r[4] = 0x3fffffffeca8;
	r[7] = 0x0;
	v(9, 0x1100ffeeddccbbaa, 0x9988776655443322);

	neg(7, 4);

	printf(HEX"| r4\n", r[4]);
	printf(HEX"| r7\n", r[7]);

	v_str(9);
	printf("%s| vr9\n", vector_str);

	return 0;
}
