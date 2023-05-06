/*
===============================================================================
 Name        : lpcopen_lpc1114fn28_ex0701_i2c_AQM0802_xprintf.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "aqm0802.h"
#include "xprintf.h"

// TODO: insert other definitions and declarations here

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    int8_t s = 0;
    int8_t m = 10;
    int8_t h = 13;

	IOCON_Config_Request();

	SysTick_Config(SystemCoreClock/1000 - 1); /* Generate interrupt each 1 s   */

	AQM0802_Config_Request();
	xdev_out(AQM0802_putc);
	AQM0802_setcursor( 0, 0 );
	xprintf ("Hello") ;
	AQM0802_setcursor( 0, 1 );
	xprintf("World");
	Delay(1000);
	AQM0802_setcursor( 0, 0 );
	xprintf("07/05/23");
	AQM0802_setcursor( 0, 1 );
	xprintf("00:00:00");

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	Delay(1000);
		i++ ;
		if(i%60 == 0) m++;
    	AQM0802_setcursor( 0, 1 );
    	xprintf("%02d:%02d:%02d", h, m, i%60);
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
