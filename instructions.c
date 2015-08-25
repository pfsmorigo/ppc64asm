#include <stdio.h>
#include <stdint.h>
#include "ppc64asm.h"

#define EXTS(x) (x << 16)
#define ROTL(x, y) (x << y)
#define MASK(x, y) (((~0ULL) << 63 - y) & (0xffffffffffffffff >> x))

void addi(uint8_t rt, uint8_t ra, uint16_t si) {
	instruction_info("Add Immediate", "D", 66, "RT,RA,SI", rt, ra, si);

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
	instruction_info("Add Immediate Shifted", "D", 66, "RT,RA,SI", rt, ra, si);

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

void cmp(uint8_t bf, uint8_t l, uint8_t ra, uint8_t rb) {
	instruction_info("Compare", "X", 78, "BF,L,RA,RB", bf, l, ra, rb);
}

void cmpdi(uint8_t ra, uint8_t si) {
	instruction_info("Compare Doubleword Immediate", "D", 78,
	                 "RA,SI", ra, si);
}

void cmpi(uint8_t bf, uint8_t l, uint8_t ra, uint8_t si) {
	instruction_info("Compare Immediate", "D", 78, "BF,L,RA,SI", bf, l, ra, si);
}

void cmpwi(uint8_t cr3, uint8_t ra, uint8_t si) {
	instruction_info("Compare Word Immediate", "", 78, "CR3,RA,SI", cr3, ra ,si);
	printf("\n");
	printf("cmpwi(%u, %u, 0x%x) == cmpi(0, 0, %u, 0x%x)\n", cr3, ra, si, ra, si);
	cmpi(3, 0, ra, si);
}

void li(uint8_t rt, uint16_t si) {
	instruction_info("Load Immediate", "", 0, "RT,SI", rt, si);
	printf("\n");
	printf("li(%u, 0x%x) == addi(%u, 0, 0x%x)\n", rt, si, rt, si);
	addi(rt, 0, si);
}

void lis(uint8_t rt, uint16_t si) {
	instruction_info("Load Immediate Shifted", "", 0, "RT,SI", rt, si);
	printf("\n");
	printf("lis(%u, 0x%x) == addis(%u, 0, 0x%x)\n", rt, si, rt, si);
	addis(rt, 0, si);
}

void lvsr(uint8_t vrt, uint8_t ra, uint8_t rb) {
	instruction_info("Load Vector for Shift Right", "X", 186,
	                 "VRT,RA,RB", vrt, ra, rb);

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
	printf("%*s | vr%u\n", 64, vector_str(generic_buffer, VRT, 2), vrt);
	printf("\n");
}

void lvx(uint8_t vrt, uint8_t ra, uint8_t rb) {
	instruction_info("Load Vector Indexed LRU", "X", 182,
	                 "VRT,RA,RB", vrt, ra, rb);
}

void mtctr(uint8_t rs) {
	instruction_info("Move To CTR", "XFX", 104, "RS", rs);
}

void mtppr(uint8_t rs) {
	instruction_info("Move To PPR (?)", "XFX", 104, "RS", rs);
}

void mtppr32(uint8_t rs) {
	instruction_info("Move To PPR32 (?)", "XFX", 104, "RS", rs);
}

void mtspr(uint8_t spr, uint8_t rs) {
	instruction_info("Move To SPR", "XFX", 104, "SPR, RS", spr, rs);
}

void neg(uint8_t rt, uint8_t ra) {
	instruction_info("Negate", "XO", 70, "RT,RA", rt, ra);

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
	instruction_info("OR Immediate", "D", 82,"RA,RS,UI", ra, rs, ui);

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
	instruction_info("OR Immediate Shifted", "D", 83, "RA,RS,UI", ra, rs, ui);

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
	instruction_info("Rotate Left Doubleword Immediate then Clear Left", "MD",
	                 94, "RA,RS,SH,ME", ra, rs, sh, me);

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
	instruction_info("Rotate Left Doubleword Immediate then Clear Right", "MD",
	                 94, "RA,RS,SH,ME", ra, rs, sh, me);

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
	instruction_info("Subtract Immediate", "", 0,
	                 "RT,RA,SI", rt, ra, si);
	printf("\n");
	printf("subi(%u, %u, 0x%x) == addi(%u, %u, (-1)0x%x)\n", rt, ra, si, rt, ra, si);
	addi(rt, 0, si*(-1));
}

void subis(uint8_t rt, uint8_t ra, uint64_t si) {
	instruction_info("Subtract Immediate Shifted", "", 0,
	                 "RT,RA,SI", rt, ra, si);
	printf("\n");
	printf("subis(%u, %u, 0x%x) == addis(%u, %u, (-1)0x%x)\n", rt, ra, si, rt, ra, si);
	addis(rt, 0, si*(-1));
}

void vperm(uint8_t vrt, uint8_t vra, uint8_t vrb, uint8_t vrc) {
	instruction_info("Vector Permute", "VA", 198,
	                 "VRT,VRA,VRB,VRC", vrt, vra, vrb, vrc);

	printf("\n");
	printf("vperm(VRT, VRA, VRB, VRC)\n");
	printf("       %2u   %2u   %2u   %2u\n", vrt, vra, vrb, vrc);
	printf("\n");

	uint64_t temp[4];
	uint8_t i, b, *temp_ptr, *vrc_ptr, *vrt_ptr;

	temp[0] = VRA[0];
	temp[1] = VRA[1];
	temp[2] = VRB[0];
	temp[3] = VRB[1];

	temp_ptr = (uint8_t *) &temp;
	vrc_ptr = (uint8_t *) &VRC;
	vrt_ptr = (uint8_t *) &VRT;

	printf("%*s | VRA (vr%u)\n", 64, vector_str(generic_buffer, VRA, 2), vra);
	printf("%*s | VRB (vr%u)\n", 64, vector_str(generic_buffer, VRB, 2), vrb);
	printf("%*s | VRC (vr%u)\n", 64, vector_str(generic_buffer, VRC, 2), vrc);
	printf("%*s | (VRA || VRB) = TEMP\n", 64, vector_str(generic_buffer, temp, 4));
	printf("\n");

	for (i = 0; i < VECTOR_SIZE; i++) {
		if (is_little_endian()) {
			b = *(vrc_ptr + VECTOR_SIZE - 1 - i);
			*(vrt_ptr + i) = *(temp_ptr + (VECTOR_SIZE * 2) - 1 - b);
		}
		else {
			b = *(vrc_ptr + i);
			*(vrt_ptr + i) = *(temp_ptr + b);
		}
		printf("      B = VRC[%2u] = 0x%02x (%2u) ---> VRT[%2u] = TEMP[B = %2u] = 0x%02x\n",
				i, b, b, i, b, *(temp_ptr +b));
	}

	printf("\n");
	printf("%*s | VRT (vr%u)\n", 64, vector_str(generic_buffer, VRT, 4), vrt);
	printf("\n");
}

void vspltisb(uint8_t vrt, uint8_t sim) {
	instruction_info("Vector Splat Immediate Signed Byte", "VX", 198,
	                 "VRT,SIM", vrt, sim);

	printf("\n");
	printf("vspltisb(VRT, SIM)\n");
	printf("          %2u  0x%02x (%u)\n", vrt, sim, sim);

	uint8_t i, *ptr;
	ptr = (uint8_t *) &VRT;

	for (i = 0; i < sizeof(uint64_t) * 2; i++)
		*(ptr+i) = sim;

	printf("\n");
	printf("%*s | VRT (vr%u)\n", 64, vector_str(generic_buffer, VRT, 2), vrt);
	printf("\n");
}

void vxor(uint8_t vrt, uint8_t vra, uint8_t vrb) {
	instruction_info("Vector Logical XOR", "VX", 239,
	                 "VRT,VRA,VRB", vrt, vra, vrb);

	printf("\n");
	printf("vxor(VRT, VRA, VRB)\n");
	printf("      %2u   %2u   %2u\n", vrt, vra, vrb);
	printf("\n");

	printf("%*s | VRA (vr%u)\n", 64, vector_str(generic_buffer, VRA, 2), vra);
	printf("%*s | VRB (vr%u)\n", 64, vector_str(generic_buffer, VRB, 2), vrb);

	VRT[0] = VRA[0]^VRB[0];
	VRT[1] = VRA[1]^VRB[1];

	printf("%*s | VRT (vr%u)\n", 64, vector_str(generic_buffer, VRT, 2), vrt);
	printf("\n");
}
