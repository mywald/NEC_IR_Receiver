#include "picsetup.h"

void configureports(){    
    //Init IO
    ANSELH = 0X0;         //Disable analog Ports
    ANSEL = 0X0;          //Disable analog Ports

    TRISB = 0x00;
    TRISA = 0x00;
    TRISC = 0x00;
    
    //Ports for SPI
    TRISBbits.TRISB6 = 0; //RB6=Clock as Output
    TRISBbits.TRISB4 = 1; //RB4=Serial Data In as Input
    TRISCbits.TRISC7 = 0; //RC7=Serial Data Out as Output
    TRISCbits.TRISC0 = 0; //RC0=Slave Select for Display as Output

    //Other Ports
    TRISCbits.TRISC1 = 0; //RC1=LED as Output
    TRISAbits.TRISA5 = 1; //RA5=TSOP Data as Input
    
//Timer0 Registers Prescaler= 64 - TMR0 Preset = 0 - Freq = 61.04 Hz - Period = 0.016384 seconds
T0CS = 0;  // bit 5  TMR0 Clock Source Select bit...0 = Internal Clock (CLKO) 1 = Transition on T0CKI pin
T0SE = 0;  // bit 4 TMR0 Source Edge Select bit 0 = low/high 1 = high/low
PSA = 0;   // bit 3  Prescaler Assignment bit...0 = Prescaler is assigned to the Timer0
PS2 = 1;   // bits 2-0  PS2:PS0: Prescaler Rate Select bits
PS1 = 0;
PS0 = 1;

    TMR0 = 0;  // preset for timer register
    T0IE=0;    //disable TMR0 Interrupt
    
    //Init SPI
    SSPEN = 0;           //Turn off SPI to make it configurable
    SSPSTAT= 0b01000000; //SMP=0, CKE=1,
    SSPCON = 0b00000010; //Enable SPI = false, CKP = 0, Configure as Master with CLK = FOSC/64
    SSPEN = 1;           //Turn on SPI
    SSPSTATbits.BF = 1;

    //Configure RA5 as Interrupt for TSOP
    IOCB = 0x0;           //Make RA5 to accept Interrupts
    IOCA = 0x0;           //Make RA5 to accept Interrupts
    IOCA5 = 1;            //Make RA5 to accept Interrupts


    GIE=0;                //Disable Interrupts globally (is enabled in main loop)
        
    RABIF = 0;            //Interrupt Flags reset
    INTF = 0;             //Interrupt Flags reset
    RABIE = 1;            //Enable Port-A/B-Change Interrupts
    PEIE = 0;             //Peripheral Interrupts disabled
    INTE = 0;             //External Interrupt disabled

    DISPLAY_SLAVE_SELECT = 0;
    LED = 0;
}
