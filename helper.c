#include <stdio.h>
#include <stdint.h>
#include "pwrasm.h"

uint64_t r[32];
uint64_t vr[32][2];
uint8_t generic_buffer[256];

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

void show_table() {
	int i;

	printf("--------------------------------------------------------------\n");
	printf(" Registers status\n");
	printf("--------------------------------------------------------------\n");
	for  (i = 0; i < 32; i++)
		if (r[i])
			printf(HEX" | r%u\n", r[i], i);

	for  (i = 0; i < 32; i++)
		if (vr[i][0] || vr[i][1])
			printf("%s | vr%u\n", vector_str(generic_buffer, i), i);
	printf("--------------------------------------------------------------\n");
}

uint8_t *vector_str(uint8_t *buffer, uint8_t vector_num) {
	if (vr[vector_num][1] == 0)
		sprintf(buffer, HEX, vr[vector_num][0]);
	else
		sprintf(buffer, "%16llx%016llx", vr[vector_num][1], vr[vector_num][0]);
	return buffer;
}

uint8_t *binary_str(uint8_t *buffer, uint64_t value, uint64_t size) {
    uint8_t *buffer_ptr, *value_ptr, bit;
    int16_t i, j;

	buffer_ptr = buffer;
	value_ptr = (uint8_t *) &value;

	for (i = size - 1; i >= 0; i--)
		for (j = 7; j >= 0; j--)
			*buffer_ptr++ = ((*(value_ptr + i) >> j & 1) == 0)? '0' : '1';

	*buffer_ptr = 0;
	return buffer;
}
