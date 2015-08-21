#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pwrasm.h"

uint64_t r[32];
uint64_t vr[32][2];
uint8_t generic_buffer[256];

uint8_t is_little_endian() {
	uint16_t temp = 0xaabb;
	return (*((uint8_t *) &temp) == 0xaa)? 0 : 1;
}

void print_bar(uint8_t divchar) {
	uint16_t i;
	for (i = 0; i < 80; i++) printf("%c", divchar);
	printf("\n");
}

void v(uint8_t vector_num, uint64_t high, uint64_t low) {
	vr[vector_num][0] = low;
	vr[vector_num][1] = high;
}

uint8_t *vector_str(uint8_t *buffer, uint64_t *vector, uint16_t size) {
	int8_t i;
	*buffer = 0;

	for (i = size - 1; i >= 0; i--)
		if (strlen(buffer))
			sprintf(buffer + strlen(buffer), "%016llx", *(vector + i));
		else if (*(vector + i) != 0)
			sprintf(buffer + strlen(buffer), "%llx", *(vector + i));
	return buffer;
}

uint8_t *binary_str(uint8_t *buffer, uint64_t value, uint16_t size) {
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

void instruction_info(char *desc, char *form, char *attrib, uint16_t page) {
	printf("\n");
	print_bar('-');
	printf("%s, %s-form, %s, Page %u\n", desc, form, attrib, page);
	print_bar('-');
}

void show_table() {
	int i;

	print_bar('=');
	printf(" Registers status\n");
	print_bar('-');
	for  (i = 0; i < 32; i++)
		if (r[i])
			printf(HEX" | r%u\n", r[i], i);

	for  (i = 0; i < 32; i++)
		if (vr[i][0] || vr[i][1])
			printf("%*s | vr%u\n", 64, vector_str(generic_buffer, vr[i], 2), i);
	print_bar('=');
}
