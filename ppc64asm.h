#ifndef PWRASM_H
#define PWRASM_H

#include <stdint.h>

#define HEX "%64llx"
#define RA r[ra]
#define RB r[rb]
#define RC r[rc]
#define RT r[rt]
#define RS r[rs]
#define VRA vr[vra]
#define VRB vr[vrb]
#define VRC vr[vrc]
#define VRT vr[vrt]

#define INSTRUCTION_SIZE 8
#define VECTOR_SIZE 16

/*#define instruction_info(condition, ...) \*/
	/*instruction_info_real(__func__, condition, __VA_ARGS__)*/

#define instruction_info(desc, form, page, attr) \
	instruction_info_real(__func__, desc, form, page, attr)

extern uint64_t r[32];
extern uint64_t vr[32][2];
extern uint8_t generic_buffer[256];

#endif
