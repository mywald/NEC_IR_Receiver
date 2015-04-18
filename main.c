#include "picsetup.h"
#include "framework.h"
#include "sevensegment.h"
#include "rc5.h"


void interrupt ISR() {
   /*GIE=0;              //No overlapping interrupts, so they are disabled
   if (RABIF) {          //Check if it is port A/B change Interrupt (= TSOP IRQ)
       RABIF=0;
       if (TSOP_IRQ){
          LED = !LED;
       }
   }
   GIE=1;                //Enable interrupts again
   */
        
    if (RABIF) {          //Check if it is port A/B change Interrupt (= TSOP IRQ)
       RABIF=0;
       ir_interruptHandler();
    } else if (T0IF) {
       T0IF=0;
       ir_abort(0xEE);
    }
}


void main(void) {
    configureports();
    
    LED = 1;
    delayms(700);
    LED = 0;

    GIE=1;
        
    //uint i = 0;
    while(true) {

//          uint t = TMR0;
  //        delayms(10);
        //LED=!LED;
        //displayChar(0x11);
        
//        displayed = 1;
  
        delayms(1000);
        displayChar(ir_temp_code);
    }
}

