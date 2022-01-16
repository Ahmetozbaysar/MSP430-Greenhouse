#include <msp430.h>                         // define libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int input;
char vt_chara0[5];                          // define array for store analog value that transmitted by ltoa function
char vt_chara1[5];
char vt_chara2[5];
char vt_chara3[5];
char vt_chara4[5];
char space[] = " ";
//char sens0[] = "A0: ";
//char volta1[] = " A1(NA):";
//char volta2[] = " A2(NA):";
//char sens1[] = " A3: ";
//char sens2[] = " A4: ";


unsigned int adc[5];
void ser_output(char *str);                 // function prototype
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer

    BCSCTL1= CALBC1_1MHZ;                   // Set DCO to 1 MHz
    DCOCTL = CALDCO_1MHZ;

    P1SEL = BIT1|BIT2;                      // Select UART RX/TX function on P1.1,P1.2
    P1SEL2 = BIT1|BIT2;

    P2DIR = BIT0 + BIT1 + BIT3 + BIT4 + BIT5;       // P2.1 and P2.4 output
    P2SEL = BIT1 + BIT4;                            // Timer_A1

    TA1CCR0 = 1000-1;                   // PWM period
    TA1CCTL1 = OUTMOD_7;                //Mod7 reset/set
    TA1CCTL2 = OUTMOD_7;                //Moo7 reset/set
    TA1CTL = TASSEL_2 + MC_1;           // Timer SMCLK Modo UP

    UCA0CTL1 |= UCSWRST+UCSSEL_2;       // UART Clock -> SMCLK
    UCA0BR0 = 52;                       // Baud Rate Setting for 1MHz 19200
    UCA0BR1 = 0;                        // Baud Rate Setting for 1MHz 19200
    UCA0MCTL = UCBRS_0;                 // Baud Rate Setting for 1MHz 19200
    UCA0CTL1 &= ~UCSWRST;               // Initialize UART Module

    ADC10CTL1 = INCH_4 + ADC10DIV_0 + CONSEQ_3 + SHS_0;                         // ADC Channel (P1.4), divider,  Repeat sequence of channels, Sample-and-hold source select
    ADC10CTL0 = REFON + REF2_5V + SREF_1 + ADC10SHT_3 + MSC + ADC10ON;          // Referans on, Reference-generator voltage (0 - 1.5V, 1-2.5V), Select reference,
                                                                                // sample-and-hold time, multiple sample and conversion, ADC10 ON
    ADC10AE0 = BIT4 + BIT3 + BIT0;                                              // P1.0, P1.3, P1.4 ADC options select
    ADC10DTC1 = 5;                                                              // Data Transfer Controller

    IE2 |= UCA0RXIE;                                                            // RX interrupt enabled
    __bis_SR_register(GIE);                                                     // General interrupt enabled

    while(1){
        ADC10CTL0 &= ~ENC;                                                      // enable conversion -> disable
        while (ADC10CTL1 & BUSY);
        ADC10CTL0 |= ENC + ADC10SC;                                             // enable conversion -> enable
        ADC10SA = (unsigned int)adc;

        ltoa(adc[4],vt_chara0,10); ltoa(adc[3],vt_chara1,10); ltoa(adc[2],vt_chara2,10);    // ltoa -> conversion long to string
        ltoa(adc[1],vt_chara3,10); ltoa(adc[0],vt_chara4,10);


        ser_output(vt_chara0);                        // sending Analog 0 and space
        ser_output(space);

        ser_output(vt_chara1);
        ser_output(space);

        ser_output(vt_chara2);
        ser_output(space);

        ser_output(vt_chara3);
        ser_output(space);

        ser_output(vt_chara4);

        __delay_cycles(3000000);                     // 3s delay
    }

}
void ser_output(char *str) {                         // data transmission function
    while(*str != 0){
        while (!(IFG2&UCA0TXIFG));
        UCA0TXBUF = *str++;
    }
}

#pragma vector=USCIAB0RX_VECTOR                     // RX interrupt vector
__interrupt void USCI0RX_ISR(void)
{

    input = UCA0RXBUF;
        switch(input)                               // evaluating incoming data
        {
        case 'A':

           P2OUT|=BIT3;
           //__delay_cycles(3000000);
           //P2OUT &=~ BIT3;

           break;


        case 'B':

            P2OUT|=BIT3;
            //__delay_cycles(6000000);
            //P2OUT &=~ BIT3;
           break;

        case 'C':

            P2OUT &=~ BIT3;
           //__delay_cycles(9000000);
          // P2OUT &=~ BIT3;

           break;


        case 'D':

            P2OUT|=BIT5;
            //__delay_cycles(3000000);
            //P2OUT &=~ BIT0;
           break;

        case 'E':
            P2OUT|=BIT5;
           // __delay_cycles(6000000);
            //P2OUT &=~ BIT0;
            break;

        case 'F':
            P2OUT |= BIT5;
           // __delay_cycles(9000000);
            //P2OUT &=~ BIT0;
            break;

        case 'G':

            TA1CCR1 = 250;                  // PWM duty cycle
            break;

        case 'H':

            TA1CCR1 = 600;                  // PWM duty cycle
            break;

        case 'I':

            TA1CCR1 = 950;                  // PWM duty cycle
            break;


        case 'J':

            TA1CCR2 = 150;                  // PWM duty cycle
            break;

        case 'K':

            TA1CCR2 = 450;                  // PWM duty cycle
            break;

        case 'L':

            TA1CCR2 = 950;                  // PWM duty cycle
            break;

        case 'M':

            P2OUT |= BIT0;
            break;

        case 'N':

            P2OUT &=~ BIT0;
            break;

        case 'O':

            TA1CCR1 = 0;
            break;

        case 'P':

            TA1CCR2 = 0;
            break;
        case 'R':
            P2OUT &=~ BIT5;
    }
}

