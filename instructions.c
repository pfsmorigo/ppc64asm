#include <stdio.h>
#include <stdint.h>
#include "pwrasm.h"

#define EXTS(x) (x << 16)
#define ROTL(x, y) (x << y)
#define MASK(x, y) (((~0ULL) << 63 - y) & (0xffffffffffffffff >> x))

void addi(uint8_t rt, uint8_t ra, uint16_t si) {
	instruction_info("Add Immediate", "D", "RT,RA,SI", 66);

	printf("\n");
	printf("addi(RT, RA, SI)\n");
	printf("      %2u  %2u  0x%x (%llu)\n", rt, ra, si, si);
	printf("\n");

	printf(HEX" | RA (r%u)\n", RA, ra);
	printf(HEX" | SI\n", si);

	if (ra == 0) RT = si;
	else RT = RA + si;

	printf(HEX" | RT (r%u)\n", RT, rt);
	printf("\n");
}

void addis(uint8_t rt, uint8_t ra, uint16_t si) {
	instruction_info("Add Immediate Shifted", "D", "RT,RA,SI", 66);

	printf("\n");
	printf("addis(RT, RA, SI)\n");
	printf("      %2u  %2u  0x%x (%llu)\n", rt, ra, si, si);
	printf("\n");

	printf(HEX" | RA (r%u)\n", RA, ra);
	printf(HEX" | SI\n", si);

	if (ra == 0) RT = EXTS(si);
	else RT = EXTS(RA + si);

	printf(HEX" | RT (r%u)\n", RT, rt);
	printf("\n");
}

void li(uint8_t rt, uint16_t si) {
	instruction_info("Load Immediate", "", "RT,SI", 0);
	printf("\n");
	printf("li(%u, 0x%x) == addi(%u, 0, 0x%x)\n", rt, si, rt, si);
	addi(rt, 0, si);
}

void lis(uint8_t rt, uint16_t si) {
	instruction_info("Load Immediate Shifted", "", "RT,SI", 0);
	printf("\n");
	printf("lis(%u, 0x%x) == addis(%u, 0, 0x%x)\n", rt, si, rt, si);
	addis(rt, 0, si);
}

void lvsr(uint8_t vrt, uint8_t ra, uint8_t rb) {
	instruction_info("Load Vector for Shift Right", "X", "VRT,RA,RB", 186);

	printf("\n");
	printf("lvsr(VRT, RA, RB)\n");
	printf("      %2u  %2u  %2u\n", vrt, ra, rb);

	uint64_t b, sh;
	uint8_t sh4;

	if (ra == 0) b = 0;
	else b = RA;

	sh = (b + RB);
	sh4 = sh & 0xf;

	switch (sh4)
	{
		case(0x0): v(vrt, 0x0001020304050607, 0x08090A0B0C0D0E0F); break;
		case(0x1): v(vrt, 0x0102030405060708, 0x090A0B0C0D0E0F10); break;
		case(0x2): v(vrt, 0x0203040506070809, 0x0A0B0C0D0E0F1011); break;
		case(0x3): v(vrt, 0x030405060708090A, 0x0B0C0D0E0F101112); break;
		case(0x4): v(vrt, 0x0405060708090A0B, 0x0C0D0E0F10111213); break;
		case(0x5): v(vrt, 0x05060708090A0B0C, 0x0D0E0F1011121314); break;
		case(0x6): v(vrt, 0x060708090A0B0C0D, 0x0E0F101112131415); break;
		case(0x7): v(vrt, 0x0708090A0B0C0D0E, 0x0F10111213141516); break;
		case(0x8): v(vrt, 0x08090A0B0C0D0E0F, 0x1011121314151617); break;
		case(0x9): v(vrt, 0x090A0B0C0D0E0F10, 0x1112131415161718); break;
		case(0xA): v(vrt, 0x0A0B0C0D0E0F1011, 0x1213141516171819); break;
		case(0xB): v(vrt, 0x0B0C0D0E0F101112, 0x131415161718191A); break;
		case(0xC): v(vrt, 0x0C0D0E0F10111213, 0x1415161718191A1B); break;
		case(0xD): v(vrt, 0x0D0E0F1011121314, 0x15161718191A1B1C); break;
		case(0xE): v(vrt, 0x0E0F101112131415, 0x161718191A1B1C1D); break;
		case(0xF): v(vrt, 0x0F10111213141516, 0x1718191A1B1C1D1E); break;
	}

	printf(HEX" | RA (r%u)\n", RA, ra);
	printf(HEX" | RB (r%u)\n", RB, rb);
	printf(HEX" | b\n", b);
	printf(HEX" | b + RB = sh\n", sh);
	printf(HEX" | sh (60:63 bits)\n", sh4);
	printf("%s | vr%u\n", vector_str(generic_buffer, vrt), vrt);
	printf("\n");
}

void neg(uint8_t rt, uint8_t ra) {
	instruction_info("Negate", "XO", "RT,RA", 70);

	printf("\n");
	printf("neg(RT, RA)\n");
	printf("    %2u  %2u\n", rt, ra);
	printf(HEX" | RA (r%u)\n", RA, ra);
	printf(HEX" | ~RA\n", ~(RA));
	printf(HEX" | ~RA + 1 = RT (r%u)\n", ~(RA) + 1, rt);
	printf("\n");

	RT = ~(RA) + 1;
}

void ori(uint8_t ra, uint8_t rs, uint16_t ui) {
	instruction_info("OR Immediate", "D", "RA,RS,UI", 82);

	printf("\n");
	printf("ori(RA, RS, UI)\n");
	printf("    %2u  %2u  %2u\n", ra, rs, ui);
	printf(HEX" | RS (r%u)\n", RS, rs);
	printf(HEX" | UI\n", ui);
	printf(HEX" | RS || UI\n", RS | ui);
	printf("\n");

	RA = (RS | ui);
}

void oris(uint8_t ra, uint8_t rs, uint16_t ui) {
	instruction_info("OR Immediate Shifted", "D", "RA,RS,UI", 83);

	printf("\n");
	printf("oris(RA, RS, UI)\n");
	printf("    %2u  %2u  %2u\n", ra, rs, ui);
	printf(HEX" | RS (r%u)\n", RS, rs);
	printf(HEX" | UI\n", ui);
	printf(HEX" | RS || UI\n", EXTS(RA | ui));
	printf("\n");

	RA = EXTS(RS | ui);
}

void rldicl(uint8_t ra, uint8_t rs, uint8_t sh, uint8_t me) {
	instruction_info("Rotate Left Doubleword Immediate then Clear Left", "MD", "RA,RS,SH,ME", 94);

	printf("\n");
	printf("rldicl(RA, RS, SH, ME)\n");
	printf("       %2u  %2u  %2u  0x%x\n", ra, rs, sh, me);
	printf(HEX" | RS (r%u)\n", RS, rs);
	printf(HEX" | ME\n", MASK(me, 63));

	RA = ROTL(RS, sh) & MASK(me, 63);

	printf(HEX" | RA (r%u)\n", RA, ra);
	printf("\n");
}

void rldicr(uint8_t ra, uint8_t rs, uint8_t sh, uint8_t me) {
	instruction_info("Rotate Left Doubleword Immediate then Clear Right", "MD", "RA,RS,SH,ME", 94);

	printf("\n");
	printf("rldicr(RA, RS, SH, ME)\n");
	printf("       %2u  %2u  %2u  %2u\n", ra, rs, sh, me);
	printf(HEX" | RS (r%u)\n", RS, rs);
	printf(HEX" | ME\n", MASK(0, me));

	RA = ROTL(RS, sh) & MASK(0, me);

	printf(HEX" | RA (r%u)\n", RA, ra);
	printf("\n");
}

void subi(uint8_t rt, uint8_t ra, uint64_t si) {
	instruction_info("Subtract Immediate", "", "RT,RA,SI", 0);
	printf("\n");
	printf("subi(%u, %u, 0x%x) == addi(%u, %u, (-1)0x%x)\n", rt, ra, si, rt, ra, si);
	addi(rt, 0, si*(-1));
}

void subis(uint8_t rt, uint8_t ra, uint64_t si) {
	instruction_info("Subtract Immediate Shifted", "", "RT,RA,SI", 0);
	printf("\n");
	printf("subis(%u, %u, 0x%x) == addis(%u, %u, (-1)0x%x)\n", rt, ra, si, rt, ra, si);
	addis(rt, 0, si*(-1));
}

void vperm(uint8_t vrt, uint8_t vra, uint8_t vrb, uint8_t vrc) {
	instruction_info("Vector Permute", "VA", "VRT,VRA,VRB,VRC", 198);

	printf("\n");
	printf("vperm(VRT, VRA, VRB, VRC)\n");
	printf("       %2u   %2u   %2u   %2u\n", vrt, vra, vrb, vrc);
	printf("\n");



}

void vspltisb(uint8_t vrt, uint8_t sim) {
	instruction_info("Vector Splat Immediate Signed Byte", "VX", "VRT,SIM", 198);

	printf("\n");
	printf("vspltisb(VRT, SIM)\n");
	printf("          %2u  0x%02x (%u)\n", vrt, sim, sim);

	uint8_t i, *ptr;
	ptr = (uint8_t *) &VRT;

	for (i = 0; i < sizeof(uint64_t) * 2; i++)
		*(ptr+i) = sim;

	printf("\n");
	printf("%s | VRT (vr%u)\n", vector_str(generic_buffer, vrt), vrt);
	printf("\n");
}

void vxor(uint8_t vrt, uint8_t vra, uint8_t vrb) {
	instruction_info("Vector Logical XOR", "VX", "VRT,VRA,VRB", 239);

	printf("\n");
	printf("vxor(VRT, VRA, VRB)\n");
	printf("      %2u   %2u   %2u\n", vrt, vra, vrb);
	printf("\n");

	printf("%s | VRA (vr%u)\n", vector_str(generic_buffer, vra), vra);
	printf("%s | VRB (vr%u)\n", vector_str(generic_buffer, vrb), vrb);

	VRT[0] = VRA[0]^VRB[0];
	VRT[1] = VRA[1]^VRB[1];

	printf("%s | VRT (vr%u)\n", vector_str(generic_buffer, vrt), vrt);
	printf("\n");
}
