#include <msp430.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;   //DISABLE THE GPIO POWER ON DEFAULT HIGH IMPEDANCE MODE

    volatile unsigned int count=0;
    P1DIR |= BIT0;

    P2DIR &= ~BIT7;
    P2OUT |=BIT7;
    P2REN |=BIT7;



    while(1){
    if(!(P2IN & BIT7)){
    P1OUT ^= BIT0;   //TURN ON THE LED
    __delay_cycles(1000000);
    count++;

    }
    }

}
