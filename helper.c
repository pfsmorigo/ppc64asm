#include <stdio.h>
#include <stdint.h>
#include "pwrasm.h"

void *v_str(uint8_t vector_num) {
	if (vr[vector_num][1] == 0)
		sprintf(vector_str, HEX, vr[vector_num][0]);
	else
		sprintf(vector_str, "%16llx%016llx", vr[vector_num][1],
				vr[vector_num][0]);
}

void v(uint8_t vector_num, uint64_t high, uint64_t low) {
	vr[vector_num][0] = low;
	vr[vector_num][1] = high;
}

void instruction_info(char *desc, char *form, char *attrib, uint16_t page) {
	printf("\n");
	printf("--------------------------------------------------------------\n");
	printf("%s, %s-form, %s, Page %u\n", desc, form, attrib, page);
	printf("--------------------------------------------------------------\n");
}
