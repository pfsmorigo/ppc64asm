#ifndef PWRASM_H
#define PWRASM_H

#include <stdint.h>

#define HEX "%32llx"
#define RA r[ra]
#define RB r[rb]
#define RC r[rc]
#define RT r[rt]
#define RS r[rs]
#define VRA vr[vra]
#define VRB vr[vrb]
#define VRC vr[vrc]
#define VRT vr[vrt]

extern uint64_t r[32];
extern uint64_t vr[32][2];
extern uint8_t generic_buffer[256];

#endif
