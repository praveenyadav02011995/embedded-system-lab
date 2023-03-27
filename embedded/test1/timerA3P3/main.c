*DESCRIPTION:
* demonstration on how to use "OUTMODE" to generate PWM signals
 *
 * This program generates two PWM outputs on P1.1,P1.2 using Timer0_A configured for up mode. *The value in CCR0, 1000-1, defines the PWM period
 * The values in CCR1 and CCR2 the PWM duty cycles.
* Using ~1MHz SMCLK as TACLK, the timer period is ~1ms with a 75% duty cycle on P1.1 and 25% on P1.2.
 *
*/

#include <msp430.h>

int main(void)
 {
 WDTCTL = WDTPW | WDTHOLD; // Stop WDT

 P1DIR |= BIT1 | BIT2; // P1.1 and P1.2output
 P1SEL1 |= BIT1 | BIT2; // P1.1 and P1.2options select

 // Disable the GPIO power-on default high-impedance mode toactivate
 // previously configured port settings
 PM5CTL0 &= ~LOCKLPM5;

 TA0CCR0 = 1000-1; // PWM Period

 TA0CCTL1 = OUTMOD_7; // CCR1 reset/set
 TA0CCR1 = 750; // CCR1 PWM duty cycle34 TA0CCTL2 = OUTMOD_7; // CCR2 reset/set
PM35 TA0CCR2 = 250; // CCR2 PWM duty cycle36 TA0CTL = TASSEL__SMCLK | MC__UP | TACLR; // SMCLK, up modeclear TAR

 __bis_SR_register(LPM0_bits); // Enter LPM0
 __no_operation(); // For debugger
