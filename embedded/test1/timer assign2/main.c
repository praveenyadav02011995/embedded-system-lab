
#include <msp430.h>
#define NUMBER_TIMER_CAPTURES 20
volatile unsigned int timerAcaptureValues[NUMBER_TIMER_CAPTURES];
unsigned int timerAcapturePointer = 0;
int main(void)
 {
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

 // Configure GPIO
 P1DIR |= BIT0; // Set P1.0 as output
 P1OUT |= BIT0; // P1.0 high
 P1SEL1 |= BIT2; // TA0.CCI2A input capture pin, second function
 P1REN |= BIT2; // enable internal pull-down resistor
 P1OUT &= ~BIT2;
 // Disable the GPIO power-on default high-impedance mode to activate
 // previously configured port settings
 PM5CTL0 &= ~LOCKLPM5;

 // Timer0_A3 Setup
 TA0CCTL2 |= CM_1 | CCIS_0 | CCIE | CAP | SCS;
 // Capture rising edge,
 //Synchronous capture,
 // Enable capture mode,
 // Enablecapture interrupt

 TA0CTL |= TASSEL_2 | MC_2 | TACLR; // Use SMCLK as clock source, clear TA0R
 // Start timer in continuous mode

 __bis_SR_register(LPM0_bits | GIE);
 __no_operation();
 }

 // Timer0_A3 CC1-2, TA Interrupt Handler


 #pragma vector = TIMER0_A1_VECTOR
 __interrupt void TIMER0_A1_ISR(void)
 {
 switch(__even_in_range(TA0IV,TA0IV_TAIFG))
 {
 case TA0IV_NONE:
 break; // No interrupt
 case TA0IV_TACCR1:
 break; // CCR1 not used
 case TA0IV_TACCR2:
 timerAcaptureValues[timerAcapturePointer++] =
TA0CCR2;
 if (timerAcapturePointer >= 20)
 {
 while (1)
 {
 P1OUT ^= 0x01; // Toggle P1.0 (LED)
 __delay_cycles(100000);
 }
 }
 break; // CCR2 not used
 case TA0IV_TAIFG:
 break; // overflow
 default:
 break;
 }
 }


