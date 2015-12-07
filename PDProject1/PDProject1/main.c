//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <string.h>

// Port_0_0 - Port_0_5 are the 6 led pins
#define TOP_BLUE (1 << 4)
#define TOP_RED (1 << 2)
#define TOP_GREEN (1 << 0)

#define BOT_BLUE (1 << 5)
#define BOT_RED (1 << 3)
#define BOT_GREEN (1 << 1)

// intensities
unsigned char inten[6];

#pragma  ioport   EP1DATA_0:    0x058
BYTE              EP1DATA_0;
#pragma  ioport   EP1DATA_1:    0x059
BYTE              EP1DATA_1;
#pragma  ioport   EP1DATA_2:    0x05A
BYTE              EP1DATA_2;
#pragma  ioport   EP1DATA_3:    0x05B
BYTE              EP1DATA_3;
#pragma  ioport   EP1DATA_4:    0x05C
BYTE              EP1DATA_4;
#pragma  ioport   EP1DATA_5:    0x05D
BYTE              EP1DATA_5;

void main(void) {
	unsigned char cnt, dat;
	
	// init intensities
	memset(inten, 0, 6);
	
	// testing
	//inten[0] = 10;
	
	// enable sleep timer
	//INT_MSK0 |= INT_MSK0_SLEEP;
	
	// enable all interrupts
	M8C_EnableGInt;
	
	// wait for enumeration
	USB_Start(0);
	while (!USB_bGetConfiguration()){}
	USB_EnableEP(1);
	
	//USB_bReadOutEP
	
	cnt = 0;
	while (1) {
		dat = 0;
		
		if (USB_bGetEPCount(1) == 6) {
			USB_bReadOutEP(1, inten, 6);
			USB_EnableEP(1);
		}
		
		// 100% isn't possible...err
		if (cnt < inten[0]) dat |= TOP_BLUE;
		if (cnt < inten[1]) dat |= TOP_RED;
		if (cnt < inten[2]) dat |= TOP_GREEN;
		if (cnt < inten[3]) dat |= BOT_BLUE;
		if (cnt < inten[4]) dat |= BOT_RED;
		if (cnt < inten[5]) dat |= BOT_GREEN;
		
		P0DATA = dat;
		
		// will rollover
		cnt += 1;
	}
}
