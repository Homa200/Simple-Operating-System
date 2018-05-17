//////////////////////////////////////////////
// Originally created for osdever.net,
// Distrobuted with OS Creator, legal notice follows:
// This code was made for the tutorial:
// "Making a Simple C kernel with Basic printf and clearscreen Functions"
//
// This code comes with absolutly
// NO WARRANTY
// you can not hold me(KJ), nor
// anyone else responsible for what
// this code does.
//
// This code is in the public domain,
// you may use it however you want
//////////////////////////////////////////////


#include "video.h"
#include "panic/panic.h"
#include "i386/ata.h"
#include "i386/cpu.h"


void kmain() // like main in a normal C program
{
	cls();
	chg_color(BG_BLACK | GREEN);
	print("Loading kernel...\n");
	print("[\n");
	cpu_detect();
	create_descriptor();
	install_gdt();
	loadGDT();
	ata_test();
    print("\n]\n");
	panic();
	for(;;);
};

