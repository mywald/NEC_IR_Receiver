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
    
    
    //Setup Timer2
    //T2CON = 0b00001100;  //Enable Timer2 with Postscaler=1:2 and Prescaler=1 = ca. 2kHz

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
    INTEDG = 1;           //Interrupt should occur on rising edge

    DISPLAY_SLAVE_SELECT = 0;
    LED = 0;
}
