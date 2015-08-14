#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HEX "%32llx"
#define RA r[ra]
#define RB r[rb]
#define RC r[rc]
#define RT r[rt]

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

void instruction_info(char *desc, char *form, char *attrib, uint16_t page) {
	printf("--------------------------------------------------------------\n");
	printf("%s, %s-form, %s, Page %u\n", desc, form, attrib, page);
	printf("--------------------------------------------------------------\n");
}

void neg(uint8_t rt, uint8_t ra) {
	instruction_info("Negate", "XO", "RT,RA", 70);

	printf("\n");
	printf("neg(RT, RA)\n");
	printf("    %2u  %2u\n", rt, ra);
	printf(HEX"| RA (r%u)\n", RA, ra);
	printf(HEX"| ~RA\n", ~(RA));
	printf(HEX"| ~RA + 1 = RT (r%u)\n", ~(RA) + 1, rt);
	printf("\n");

	RT = ~(RA) + 1;
}

void lvsr(uint8_t vtr, uint8_t ra, uint8_t rb) {
	instruction_info("Load Vector for Shift Right", "X", "VTR,RA,RB", 186);

	printf("\n");
	printf("lvsr(VTR, RA, RB)\n");
	printf("      %2u  %2u  %2u\n", vtr, ra, rb);

	uint64_t b, sh;
	uint8_t sh4;

	if (ra == 0) b = 0;
	else b = RA;

	sh = (b + RB);
	sh4 = sh & 0xf;

	switch (sh4)
	{
		case(0x0): v(vtr, 0x0001020304050607, 0x08090A0B0C0D0E0F); break;
		case(0x1): v(vtr, 0x0102030405060708, 0x090A0B0C0D0E0F10); break;
		case(0x2): v(vtr, 0x0203040506070809, 0x0A0B0C0D0E0F1011); break;
		case(0x3): v(vtr, 0x030405060708090A, 0x0B0C0D0E0F101112); break;
		case(0x4): v(vtr, 0x0405060708090A0B, 0x0C0D0E0F10111213); break;
		case(0x5): v(vtr, 0x05060708090A0B0C, 0x0D0E0F1011121314); break;
		case(0x6): v(vtr, 0x060708090A0B0C0D, 0x0E0F101112131415); break;
		case(0x7): v(vtr, 0x0708090A0B0C0D0E, 0x0F10111213141516); break;
		case(0x8): v(vtr, 0x08090A0B0C0D0E0F, 0x1011121314151617); break;
		case(0x9): v(vtr, 0x090A0B0C0D0E0F10, 0x1112131415161718); break;
		case(0xA): v(vtr, 0x0A0B0C0D0E0F1011, 0x1213141516171819); break;
		case(0xB): v(vtr, 0x0B0C0D0E0F101112, 0x131415161718191A); break;
		case(0xC): v(vtr, 0x0C0D0E0F10111213, 0x1415161718191A1B); break;
		case(0xD): v(vtr, 0x0D0E0F1011121314, 0x15161718191A1B1C); break;
		case(0xE): v(vtr, 0x0E0F101112131415, 0x161718191A1B1C1D); break;
		case(0xF): v(vtr, 0x0F10111213141516, 0x1718191A1B1C1D1E); break;
	}

	printf(HEX"| RA (r%u)\n", RA, ra);
	printf(HEX"| RB (r%u)\n", RB, rb);
	printf(HEX"| b\n", b);
	printf(HEX"| b + RB = sh\n", sh);
	printf(HEX"| sh (60:63 bits)\n", sh4);
	v_str(vtr);
	printf("%s| vr%u\n", vector_str, vtr);
	printf("\n");
}


int main(int argc, char **argv)
{
	r[4] = 0x3fffffffeca8;
	r[7] = 0x0;
	v(9, 0x1100ffeeddccbbaa, 0x9988776655443322);

	neg(7, 4);
	lvsr(5, 0, 7);

	return 0;
}
