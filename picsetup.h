#ifndef PICSETUP_H
#define	PICSETUP_H

#include <xc.h>            /* XC8 General Include File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/******************************************************************************/
/* CHIP Setup
/******************************************************************************/
#define _XTAL_FREQ 2000000
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#define LED RC1
#define TSOP_IRQ RA5
#define DISPLAY_SLAVE_SELECT RC0


/* --- RC5 driver configuration --- */
#define RC5_DATA_PIN          RA5
#define RC5_TICKS_PER_MS      (1000/26)     /* timer increments every 25.6us, */
#define RC5_TIMER             TMR0


void configureports();


#endif	/* PICSETUP_H */

