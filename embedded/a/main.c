#include <msp430.h>


/**
 * main.c
 */
#define LED BIT0  //BIT0 is assigned to variable name led
#define BUTTON BIT3 //BIT3 is assigned to variable name Button
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= LED;

    P2DIR &= ~BUTTON; //direction is set as input
    P2REN |= BUTTON;  //Resistor enable
    P2OUT |= BUTTON;  //pullup mode

    P2IE |= BUTTON;   //interrupt enabled for P2.3
    P2IES |= BUTTON; //interrupt edge select _ falling edge high to low
    P2IFG &= 0x00;   //clear the interrupt flag
    __bis_SR_register(GIE);  //enable global interrupt

    while(1);  //infinite loop, waiting for interrupt
}

#pragma vector= PORT2_VECTOR //#pragma sets up an interrupt vector
__interrupt void PORT2_ISR(void)  //__interrupt tells the compiler to code this function as an ISR
  {
   if (P2IFG & BUTTON)
    {
        P1OUT ^= LED;  //toggle led
        P2IFG &= ~BUTTON;  //clear the interrupt flag

    }
}
