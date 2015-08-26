#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h> // free()
#include "ppc64asm.h"

uint64_t r[32];
uint64_t vr[32][2];
uint8_t generic_buffer[256];

struct attribute {
	uint8_t name[5];
	uint16_t value;
};

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

void general_info() {
	printf("General Info\n");
	print_bar('-');
	printf("\n");
	printf("    RA, RB, RC, RT: General Purpose Register    ");
	printf("    SI: Signed Integer\n");
	printf("    VRA, VRB, VRC, VRT: Vector Register         ");
	printf("    UI: Unsigned Integer\n");
}

void instruction_info_real(uint8_t *name, uint8_t *desc, uint8_t *form,
                           uint16_t page, uint8_t *attr, uint16_t value, ...) {
	uint8_t *ch;
	uint8_t *str;
	int8_t i, num;
	uint8_t title[2][100];
	struct attribute attributes[10];
	va_list values;

	str = strdup(attr);
	ch = strtok(str, ",");

	va_start(values, value);
	num = 0;
	while (ch != NULL) {
		strcpy(attributes[num].name, ch);
		attributes[num++].value = value;
		value = va_arg(values, uint64_t);
		ch = strtok(NULL, ",");
	}
	va_end(values);
	free(str);

	sprintf(title[0], "\n%s(", name);
	sprintf(title[1], "%*s", strlen(name) - 1, " ");

	for  (i = 0; i < num; i++)
	{
		sprintf(title[0] + strlen(title[0]), "%s", attributes[i].name);
		if (i != num - 1)
			sprintf(title[0] + strlen(title[0]), ", ");
		else
			sprintf(title[0] + strlen(title[0]), ")");

		sprintf(title[1] + strlen(title[1]), "%*u",
				strlen(attributes[i].name) + 2, attributes[i].value);
	}

	sprintf(title[0] + strlen(title[0]), "%-*s, %s-form",
			73 - strlen(title[0]), desc, form);

	sprintf(title[1] + strlen(title[1]), "%-*s %u", 77 - strlen(title[1]),
			"Page", page);

	printf("\n\n%s\n%s\n", title[0], title[1]);
	print_bar('-');
	printf("\n");
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
