#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	void transmit_data()
	 {
	    TMOD = 0x20;
	    TH1 = 0xfd;
	    PCON &= 0x7f;
	SCON = 0x50;
	TCON =0x40;
	while(1)
	  {
	    printf("a"); // transmit a along with CR & LF.
	  }

	return 0;
}
