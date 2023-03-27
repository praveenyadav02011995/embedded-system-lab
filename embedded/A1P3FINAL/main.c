#include <msp430.h>


/**
 * main.c
 */
#define LEDR BIT0  //BIT0 is assigned to variable name led
#define LEDG BIT1
#define BUTTONR BIT3 //BIT3 is assigned to variable name Button
#define BUTTONG BIT7
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= LEDR;
    P1DIR |= LEDG;


    P2DIR &= ~BUTTONR; //direction is set as input
    P2REN |= BUTTONR;  //Resistor enable
    P2OUT |= BUTTONR;  //pullup mode

    P2DIR &= ~BUTTONG; //direction is set as input
     P2REN |= BUTTONG;  //Resistor enable
     P2OUT |= BUTTONG;  //pullup mode




    P2IE |= BUTTONR;   //interrupt enabled for P2.3
    P2IES |= BUTTONR; //interrupt edge select _ falling edge high to
    P2IE |= BUTTONG;   //interrupt enabled for P2.3
    P2IES |= BUTTONG; //interrupt edge select _ falling edge high to low
    P2IFG &= 0x00;   //clear the interrupt flag
    __bis_SR_register(GIE);  //enable global interrupt

    while(1);  //infinite loop, waiting for interrupt
}

#pragma vector= PORT2_VECTOR //#pragma sets up an interrupt vector
__interrupt void PORT2_ISR(void)  //__interrupt tells the compiler to code this function as an ISR
{

   if (P2IFG & BUTTONR)
    {

       P1OUT ^= LEDR;  // led
        P2IFG &= ~BUTTONR;  //clear the interrupt flag

    }
   if (P2IFG & BUTTONG)
       {

           P1OUT ^= LEDG;  //toggle led
           P2IFG &= ~BUTTONG;  //clear the interrupt flag
       }

}

