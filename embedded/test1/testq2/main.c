#include <msp430.h> 


/**
 * main.c
 */
void key();
    /*
     *
     */
    void key()
    {
        P1DIR |= BIT0; // P1.0 as output port

        P1DIR |= (BIT6|BIT7|BIT3);   // P1.3,P1.6,P1.7 as output port
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

      PM5CTL0 &= ~LOCKLPM5; // disable GPIO power default high impedence mode
      int i; // declare variable i
      int j;// declare variable j

      key();

      while(1)
      {
          P1OUT &= ~BIT3; // disable port 1.3 pin
                         P2OUT |= BIT4; // enable port 2.4 pin
                                 P1OUT |= BIT7; // enable port 1.7 pin
                         P1OUT |= BIT6; // enable port 1.6 pin

                         {


    for (i=0; i<1600; i++){        //loop for high output
        P1OUT |= BIT3;   // low output at P1.3
        __delay_cycles(100000); // delay for reducing debouncing
    }
    for (j=0; j<1600; j++){       //loop for low output
           P1OUT & ~BIT3;         //low output at P1.3
           __delay_cycles(100000); //delay for reducing debouncing
       }
                         }                       }
    return 0;
}
