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
        
   RC5_InterruptHandler();
   RABIF=0;
}


void main(void) {
    configureports();
    
    LED = 1;
    delayms(700);
    LED = 0;

    GIE=1;

    while(1) {
        if (RC5_CodeReady()) {
            LED = 1;
            
            uint16 rc5code = RC5_GetCode();
                
            RC5_GetDeviceAddr(rc5code);
            RC5_GetToggleBit(rc5code);
            RC5_GetCmd(rc5code);
        }
        
        displayChar(RC5_GetCmd(rc5_code_tmp));
        delayms(1000);
        RC5_TimeoutIncrement();
    }
}

