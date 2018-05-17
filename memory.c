/*
MU-2006 memory fucntions.

*/


#include "memory.h"
#include "stdio.h"
#include "stdint.h"
#include "../video.h "

static inline char inb(short port)
{
    char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}


static inline void outb(short port, char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );

}


int getCMOSMemory() // from DiamOS
{
    unsigned short total;
    unsigned char lowmem, highmem;
 
    outb(0x70, 0x30);
    lowmem = inb(0x71);
    outb(0x70, 0x31);
    highmem = inb(0x71);
 
    total = lowmem | highmem << 8;
    return total;
    return 500000;
}



uint32_t kmalloc(uint32_t sz)
{
  uint32_t placement_address = 0;
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
} 