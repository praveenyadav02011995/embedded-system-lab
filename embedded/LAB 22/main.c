
	
#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    UCA0CTLW0 |= UCSWRST;
    UCA0CTLW0 |=UCSSEL__SMCLK;
    UCA0BRW = 6;
    UCA0MCTLW= 0X9220;


    P1SEL1 &= ~BIT4;
    P1SEL0 |= BIT4;

    PM5CTL0 &= ~LOCKLPM5;

    UCA0CTLW0 &= ~UCSWRST;
int i;
    while(1)
    {
        UCA0TXBUF = 'B';
        for (i=0;i<10000;i++)
        {}
    }



}


