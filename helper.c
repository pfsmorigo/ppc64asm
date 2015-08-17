#include <stdio.h>
#include <stdint.h>
#include "pwrasm.h"

uint64_t r[32];
uint64_t vr[32][2];
uint8_t generic_buffer[256];

void *v_str(uint8_t vector_num) {
	if (vr[vector_num][1] == 0)
		sprintf(generic_buffer, HEX, vr[vector_num][0]);
	else
		sprintf(generic_buffer, "%16llx%016llx", vr[vector_num][1],
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

void show_table() {
	int i;

	printf("--------------------------------------------------------------\n");
	for  (i = 0; i < 32; i++)
		if (r[i])
			printf(HEX" | r%u\n", r[i], i);

	for  (i = 0; i < 32; i++)
		if (vr[i][0] || vr[i][1]) {
			v_str(i);
			printf("%s | vr%u\n", generic_buffer, i);
		}
	printf("--------------------------------------------------------------\n");
}

uint64_t *binary_str(char *buffer, unsigned int value, uint64_t size) {
    char *buffer_ptr = buffer;

    if (value == 0) {
        *buffer_ptr++ = '0';
        *buffer_ptr = 0;
        return buffer;
    }

    buffer_ptr += size;
    *buffer_ptr-- = 0;

    while (value != 0) {
        if (size-- == 0) return NULL;
        *buffer_ptr-- = ((value & 1) == 1) ? '1' : '0';
        value >>= 1;
    }
    return buffer_ptr + 1;
}
