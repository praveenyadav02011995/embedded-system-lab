#include <msp430.h>

void key();
/*
 *
 */
void key()
{
    P1DIR |= BIT0;

    P1DIR |= (BIT6|BIT7|BIT3);   // P1.6,P1.7,P1.3 as output port
    P2DIR |= BIT4;              // P2.4 as output port

    P2DIR &= ~(BIT5|BIT6);      // P2.5,P2.6 as input port
    P3DIR &= ~(BIT1|BIT2);      // P3.1,P3.2 as input port
    P2REN |= (BIT5|BIT6);      //enabling P2.5, P2.6 for pullup/pulldown
    P3REN |= (BIT1|BIT2);      //enabling P3.1, P3.2 for pullup/pulldown
    P2OUT |= (BIT5|BIT6);      //pullup
    P3OUT |= (BIT1|BIT2);      //pullup
}
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

  PM5CTL0 &= ~LOCKLPM5;

  key();

  while(1)
    {

             P1OUT &= ~BIT3;
             P2OUT |= BIT4;
             P1OUT |= BIT7;


             if(!(P3IN & BIT2))   //D4
         {
             P1OUT |= BIT0;
            __delay_cycles(100000);
            P1OUT &= ~BIT0;
            __delay_cycles(100000);
                   key();   // initializing the keypad

         }
             P2OUT &= ~BIT4;

                         P1OUT |= BIT7;
                         P1OUT |= BIT3;

                         if(!(P2IN & BIT6))   //D4
                     {
                         P1OUT |= BIT0;
                        __delay_cycles(100000);
                        P1OUT &= ~BIT0;
                        __delay_cycles(100000);
                               key();   // initializing the keypad

                     }
                         P1OUT &= ~BIT3;
                                     P2OUT |= BIT4;
                                     P1OUT |= BIT7;
                                     P1OUT |= BIT6;

                                     if(!(P3IN & BIT2))   //D4
                                 {
                                     P1OUT |= BIT0;
                                    __delay_cycles(100000);
                                    P1OUT &= ~BIT0;
                                    __delay_cycles(100000);
                                           key();   // initializing the keypad

                                 }
 }
 }
