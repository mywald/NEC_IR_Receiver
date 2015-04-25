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
    
    //Init SPI
    SSPEN = 0;           //Turn off SPI to make it configurable
    SSPSTAT= 0b01000000; //SMP=0, CKE=1,
    SSPCON = 0b00000010; //Enable SPI = false, CKP = 0, Configure as Master with CLK = FOSC/64
    SSPEN = 1;           //Turn on SPI
    SSPSTATbits.BF = 1;

    GIE=1;                //Enable Interrupts globally
    RABIF = 0;            //Interrupt Flags reset
    INTF = 0;             //Interrupt Flags reset
    RABIE = 1;            //Enable Port-A/B-Change Interrupts
    PEIE = 0;             //Peripheral Interrupts disabled
    INTE = 0;             //External Interrupt disabled

    DISPLAY_SLAVE_SELECT = 0;
    LED = 0;
}
