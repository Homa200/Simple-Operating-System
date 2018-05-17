#include "panic.h"



void panic()
{
	chg_color(BG_BLUE | WHITE);
	print("Oops, SOS crashed :(");
	while(1);
}