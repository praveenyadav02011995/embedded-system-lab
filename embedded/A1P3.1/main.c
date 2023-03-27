#include <msp430.h> 
#define LEDR BIT0// BIT0 IS A VARIABLE NAME LED
#define LEDG BIT1// BIT1 IS A BARIABLE NAME LED
#define BUTTONR BIT3//BIT3 IS ASSIGNNED AS NAME BUTTON
#define BUTTONG BIT7
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= LEDR;
	P1DIR |= LEDG;

	P2DIR &= ~BUTTONR;
	P2OUT |= BUTTONR;
	P2REN |= BUTTONR;

	P2DIR &= BUTTONG;
	P2OUT |= BUTTONG;
	P2REN |= BUTTONG;

	P2IE |= BUTTONR;
	P2IES |= BUTTONR;

	P2IE |= BUTTONG;//interupt enable for port 2 pin7
	P2IES |= BUTTONG;//interrupt edge select falling edge high to low

	P2IFG &= 0x00;// clear the interrupt flag
	_bis_SR_register(GIE);//enable global interrupt
	while(1);
}
//#pragma vector= PORT2_VECTOR //#PRAGMA sets up the interrupt vector;
_//nterrupt void PORT2_ISR(void) //_interrupt tells the complier to code this function as an ISR

#pragma vector= PORT2_VECTOR //#pragma sets up an interrupt vector
__interrupt void PORT2_ISR(void)  //__interrupt tells the compiler to code this function as an ISR

{
    if((P2IFG & BUTTONR)){
        P1OUT ^= LEDR;
        P2IFG &= ~BUTTONR;// clear the interrupt flag
    }
	if((P2IFG & BUTTONG)){
	    P1OUT ^= LEDG;
	    P2IFG &= ~BUTTONR;
	}












	
	return 0;
}
