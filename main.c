#include "framework.h"
#include "picsetup.h"
#include "sevensegment.h"
#include "nec_ir_driver.h"


void interrupt ISR() {
    ir_interruptHandler();
}


void main(void) {
    configureports();
    ir_setup();
    
    displayChar(0x00);
        
    while(true) {
        
        if (ir_isReady()){
            fastBlink();
            displayChar(ir_popLatestCommand());
        }
        
    }
}

