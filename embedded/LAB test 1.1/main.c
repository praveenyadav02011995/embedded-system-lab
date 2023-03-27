#include <msp430.h>

void key();
/*
 *
 */
void key()
{
    P1DIR |= BIT0;

    P1DIR |= (BIT6|BIT7|BIT3|BIT2);   // P1.6,P1.7,P1.3,P1.2 as output port
    P2DIR |= BIT4;              // P2.4 as output port

    P2DIR &= ~(BIT5|BIT6);      // P2.5,P2.6 as input port
    P3DIR &= ~(BIT1|BIT2);      // P3.1,P3.2 as input port
    P2REN |= (BIT5|BIT6);      //enabling P2.5, P2.6 for pullup/pulldown
    P3REN |= (BIT1|BIT2);      //enabling P3.1, P3.2 for pullup/pulldown
    P2OUT |= (BIT5|BIT6);      //pullup
    P3OUT |= (BIT1|BIT2);      //pullup
}

void column3()

  {

           P1OUT |= BIT3;
           P2OUT |= BIT4;
           P1OUT &= ~BIT7;
           P1OUT |= BIT6;

           if(!(P3IN & BIT2))   // If key 1 is pressed then store 1 in variable x and generate 1KHz frequency
       {
               x=3;
             for(i=0;i<5000;i++)
             {
            P1OUT^=BIT2;
          __delay_cycles(500/3);
               }
           key();   // initializing the keypad
       }


           if(!(P2IN & BIT6))   // If key 4 is pressed then store 4 in variable x and generate 4KHz frequency
                    {
                            x=6;
                          for(i=0;i<5000;i++)
                          {
                         P1OUT^=BIT2;
                       __delay_cycles(500/6);
                            }
                        key();   // initializing the keypad
                    }

           if(!(P2IN & BIT5))   // If key 7 is pressed then store 7 in variable x and generate 7KHz frequency
                    {
                            x=9;
                          for(i=0;i<5000;i++)
                          {
                         P1OUT^=BIT2;
                       __delay_cycles(500/9);
                          }
                        // initializing the keypad
                    }

  }


void column2();
  {

           P1OUT |= BIT3;
           P2OUT &= ~BIT4;
           P1OUT |= BIT7;
           P1OUT |= BIT6;

           if(!(P3IN & BIT2))   // If key 1 is pressed then store 1 in variable x and generate 1KHz frequency
       {
               x=2;
             for(i=0;i<5000;i++)
             {
            P1OUT^=BIT2;
          __delay_cycles(500/2);
               }
           key();   // initializing the keypad
       }


           if(!(P2IN & BIT6))   // If key 4 is pressed then store 4 in variable x and generate 4KHz frequency
                    {
                            x=5;
                          for(i=0;i<5000;i++)
                          {
                         P1OUT^=BIT2;
                       __delay_cycles(500/5);
                            }
                        key();   // initializing the keypad
                    }

           if(!(P2IN & BIT5))   // If key 7 is pressed then store 7 in variable x and generate 7KHz frequency
                    {
                            x=8;
                          for(i=0;i<5000;i++)
                          {
                         P1OUT^=BIT2;
                       __delay_cycles(500/8);
                          }
                        // initializing the keypad
                    }
           else{
               column3();
           }
  }

}


int main(void)
{
    volatile unsigned int x,i;
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

  PM5CTL0 &= ~LOCKLPM5;


key();
  while(1){
      P1OUT &= ~BIT3;
         P2OUT |= BIT4;
         P1OUT |= BIT7;
         P1OUT |= BIT6;

         if(!(P3IN & BIT2))   // If key 1 is pressed then store 1 in variable x and generate 1KHz frequency
     {
             x=1;
           for(i=0;i<5000;i++)
           {
          P1OUT^=BIT2;
        __delay_cycles(500);
             }
         key();   // initializing the keypad
     }


         if(!(P2IN & BIT6))   // If key 4 is pressed then store 4 in variable x and generate 4KHz frequency
                  {
                          x=4;
                        for(i=0;i<5000;i++)
                        {
                       P1OUT^=BIT2;
                     __delay_cycles(125);
                          }
                      key();   // initializing the keypad
                  }

         if(!(P2IN & BIT5))   // If key 7 is pressed then store 7 in variable x and generate 7KHz frequency
                  {
                          x=7;
                        for(i=0;i<5000;i++)
                        {
                       P1OUT^=BIT2;
                     __delay_cycles(500/7);
                        }
                         // initializing the keypad

                  }
         else(){
             column2();
         }
       }
  }
      }
