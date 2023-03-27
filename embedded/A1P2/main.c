#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
   PM5CTL0 &= ~LOCKLPM5;           //DISABLE THE GPIO POWER ON DEFAAULT HIGH IMPEDANCE MODE

   P1DIR |= BIT1;             // SET BIT 1 TO HIGH i.e. PIN 1 OF PORT 1 IS SET AS OUTPUT PIN
   int i;
   int j;

  while(1)
   {

       for ( i=0;i<3200;i++)
       {
           P1OUT = P1OUT | BIT1;
       }

       for (j=0;j<3200;j++)
                   {
           P1OUT = P1OUT & ~BIT1;
                   }
   }

return 0;
}

