

#include "CPU.h"

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

int cpu_detect()
{
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x756e6547: 
		   print("Detected x86 Intel CPU\n");
		   return 1;
		break;
		case 0x68747541:
		   print("Detected x86 AMD CPU\n");
		   return 2;
		break;
		case 0x52261313:
		   print("Detected x86 Lake CPU\n");
		   return 3;
		break;
		default:
		   print("Unknown x86 CPU Detected\n");
		break;
	}
	return 0;
}




