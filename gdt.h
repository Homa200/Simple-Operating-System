#ifndef __GDT_H
#define __GDT_H

//#include "../stdint/types.h"
#include <stdint.h>

void create_descriptor(uint32_t base, uint32_t limit, uint16_t flag);
void install_gdt(void);
void loadGDT(void);

#endif
