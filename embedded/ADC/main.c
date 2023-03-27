


#include <msp430.h>
#include<string.h>
int a=0;
unsigned int ADC_Result;
volatile long int m1,i;
void Initialize_gpio_lcd();
void wd(char n, int mode);

char l,m,p;
int hundreds, tens, ones,j;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                                // Stop WDT
    Initialize_gpio_lcd();


    P1DIR |= BIT0;                                           // Set P1.0/LED to output direction
    P1OUT &= ~BIT0;                                          // P1.0 LED off


    SYSCFG2 |= ADCPCTL0;


    PM5CTL0 &= ~LOCKLPM5;

    // Configure ADC10
    ADCCTL0 |= ADCSHT_2 | ADCON;      // ADCON, S&H=16 ADC clks
    ADCCTL1 |= ADCSHP;                // ADCCLK = MODOSC(internal oscillator; sampling timer,pulse mode select
    ADCCTL2 |= ADCRES;               // 10-bit conversion results
    ADCMCTL0 |= ADCINCH_0;           // A1 ADC input select; Vref=AVcc
    ADCIE |= ADCIE0;                // Enable ADC conv complete interrupt

    while(1)
    {
        ADCCTL0 |= ADCENC | ADCSC;                           // Sampling and conversion start
        __bis_SR_register(LPM0_bits | GIE);                  // LPM0, ADC_ISR will force exit
        //__no_operation();                                    // For debug only
        if (ADC_Result < 0x1FF)
            P1OUT &= ~BIT0;                                  // Clear P1.0 LED off
        else
            P1OUT |= BIT0;                                   // Set P1.0 LED on
        __delay_cycles(5000);
    }
    wd(0x01,1);//clear the display
}

// ADC interrupt service routine

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)

{

            wd(0x80,1); //initialize the cursor to the first position
            wd(0x06,1);  //entry mode

            ADC_Result = ADCMEM0;

            j=ADC_Result;

            ones = j%10;
            j = j/10;
            tens = j%10;
            hundreds = j/10;




            p = hundreds | 0x30;
            wd(p,0);  //data mode

            m = tens | 0x30;
            wd(m,0);  //data mode
            l = ones | 0x30;
            wd(l,0);  //data mode




            __bic_SR_register_on_exit(LPM0_bits);            // Clear CPUOFF bit from LPM0

}



void Initialize_gpio_lcd()   //calling function
{
   P2DIR |= (BIT0 | BIT1 | BIT5 | BIT6);                         //initialize the bits
   P3DIR |= (BIT1 | BIT2);
   P2OUT |= (BIT0 | BIT1 | BIT5 | BIT6);
   P3OUT |= (BIT1 | BIT2);
   P2OUT |= BIT1;  //ENABLE PIN, LOW MEANS TRANSFER THE DATA
   for(m1=1000;m1!=0;m1--);  //delay
   wd(0x03,1);  //1 means creating the command
   for(m1=1000;m1!=0;m1--);  //delay
   //tell lcd to enable 4 bit mode
   wd(0x02,1);
   for(m1=1000;m1!=0;m1--);  //delay
   //tell the lcd to print in 2 rows, utilize both rows
   wd(0x28,1);
   //clear the display and place cursor to blinking position
   wd(0x01,1);
   wd(0x0C,1);
   wd(0x06,1);  //auto increment like I in first row 1st column, love is in 1st row 2nd clumn
   wd(0x80,1);
}
void wd(char n, int mode)
{
    int d0,d1,d2,d3,d4,d5,d6,d7;
    d0 = n & 0x01;                         //command or data
    d1 = n & 0x02;
    d2 = n & 0x04;
    d3 = n & 0x08;
    d4 = n & 0x010;
    d5 = n & 0x020;
    d6 = n & 0x040;
    d7 = n & 0x080;

    for(m1=1000;m1!=0;m1--);  //delay
    //check which mode it is, command mode or data mode
    if (mode) P2OUT &= ~BIT0; //RS select pin, if(1)
    else P2OUT |= BIT0;       //if(0)

    //send 8 bit data in 4 bit package

    if(d4) P3OUT |= BIT2; //HIGHER ORDER BITS SENT
    else P3OUT &= ~BIT2;

    if(d5) P2OUT |= BIT6;
    else P2OUT &= ~BIT6;

    if(d6) P2OUT |= BIT5;
    else P2OUT &= ~BIT5;

    if(d7) P3OUT |=BIT1;
    else P3OUT &= ~BIT1;

    for(m1=1000;m1!=0;m1--);  //delay


    P2OUT |=BIT1;
    for(m1=1000;m1!=0;m1--);  //delay
    P2OUT &= ~BIT1;

        if(d0) P3OUT |=BIT2; //lower ORDER BITS SENT
        else P3OUT &= ~BIT2;

        if(d1) P2OUT |=BIT6;
        else P2OUT &= ~BIT6;

        if(d2) P2OUT |=BIT5;
        else P2OUT &= ~BIT5;

        if(d3) P3OUT |=BIT1;
        else P3OUT &= ~BIT1;

        for(m1=1000;m1!=0;m1--);  //delay
        P2OUT |= BIT1;
        for(m1=1000;m1!=0;m1--);  //delay
        P2OUT &= ~BIT1;

}
