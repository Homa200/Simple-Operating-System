#include <stdint.h>
#include "..\video.h" 
#include "ata.h" 



/*
THIS CODE was to take from the project DiamOS 
*/


struct ide_device {
   unsigned char  Reserved;    // 0 (Empty) or 1 (This Drive really exists).
   unsigned char  Channel;     // 0 (Primary Channel) or 1 (Secondary Channel).
   unsigned char  Drive;       // 0 (Master Drive) or 1 (Slave Drive).
   unsigned short Type;        // 0: ATA, 1:ATAPI.
   unsigned short Signature;   // Drive Signature
   unsigned short Capabilities;// Features.
   unsigned int   CommandSets; // Command Sets Supported.
   unsigned int   Size;        // Size in Sectors.
   char  Model[41];   // Model in string.
} ide_devices[4];

struct IDEReg {
	
	unsigned int base; //1f7, etc
	unsigned int curr;  //port for select drive
	
} IDEReg;
/*     
    Primary Master Drive.
    Primary Slave Drive.
    Secondary Master Drive.
    Secondary Slave Drive. 
*/

 
 static inline void outb(short port, char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline char inb(short port)
{
    char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
 
 uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

 


void ata_test()
{
	
	int err = 0;
    unsigned char type = IDE_ATA;

outb(0x1F6, 0xA0); //Select drive

outb(0x1F2, 0); //SectorCount = 0
outb(0x1F3, 0); //LBAlo = 0
outb(0x1F4, 0); //LBAmid = 0
outb(0x1F5, 0); //LBAhi IO = 0

outb(0x1F7, 0xEC); //Send identify command


if(inb(0x1F7) == 0)
{
print("[ATA] Device at [Channel 1] and [Master] not found");
	print("      [NO]\n");
}
else
{
print("[ATA] Found Device at [Channel 1] and [Master]"); 
	print("      [OK]\n");
}
	outb(0x1F6, 0xA0);    //Select drive
	outb(0x1F7, 0xEC);    //Send identify command
	
	
	if(inb(0x1F7) == 0)
	{
	    print("[ IDE] Coun't found Device\n");
		err = 1;
	}
	else
	{
	    print("[ IDE] Found Device: \n");	
		err = 0;
	}
		if (err == 0) {
        unsigned char cl = inb(0x1F4); //LBA
        unsigned char ch = inb(0x1F5); //LBAmid
        
        if (cl == 0x14 && ch ==0xEB)
        {    type = IDE_ATAPI;     }
        else if (cl == 0x69 && ch == 0x96)
        {    type = IDE_ATAPI;     }
	    else
		{    type = IDE_ATA;       }
			   
	}
	
	if(err == 0)
	{
		if(type == IDE_ATA)
		{ 
	        print("ATA (HDD),\n");
        }		   
		
		if(type == IDE_ATAPI)
		{
	        print("ATAPI (CD-ROM), \n");
		}		   
	}
}


int ATAPIMediaEject(int port)
{
    outb(port, 0xED);
	return 0;
}


int ATAPIMediaLock(int port)
{
    outb(port, 0xDE);
	return 0;
}

int ATAPIMediaUNLock(int port)
{
    outb(port, 0xDF);
	return 0;
}


void ATAPIORead(int sz, void *buffer, int port)
{
	uint16_t *rdbuff = (uint16_t*)buffer;
	
	while(sz == 0)
	{
	    *rdbuff = inw(port);
        rdbuff++;	
        sz -=2;		
	}
}
