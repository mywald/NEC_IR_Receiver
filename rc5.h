/*
 * IR decoder driver
 * 
 *                                                                           
 * The following items to be configured:                                     
 * - RC5_DATA_PIN: RC5 input pin                                        
 * - RC5_TIMER:    Timer Register. 
 *                 Timer has to be configured to 51.6 ticks per uS
 *                 Which is e.g. TMR0 with 1:256 prescaler on 20MHz PIC
 *
 */
 
#include "framework.h"
#include "picsetup.h"

#ifndef RC5_DATA_PIN
#error RC5_DATA_PIN not defined!
#endif

#ifndef RC5_TIMER
#error RC5_TIMER not defined!
#endif

/* Timing setup */
#define IR_START_PERIOD_LO          140
#define IR_START_PERIOD_HI           70
#define IR_PAUSE                      8
#define IR_LOW_BIT                    8
#define IR_HIGH_BIT                  26

/* Operation modes: */
#define IR_WAIT_FOR_START        0
#define IR_WAIT_FOR_START_HI     1
#define IR_WAIT_FOR_DATA         2
#define IR_IS_READING_DATA       3
#define IR_IS_PAUSING            4

/* IR decoding status variables */
static uint16 ir_received_code = 0;  
static uint16 ir_temp_code = 0;  
static uint8 ir_bit_pos = 13;
static uint8 ir_timer_offset;
static uint8 ir_operationmode;
static bool ir_ready = FALSE;
static bool ir_pinstate_old = TRUE;

void ir_abort(uint16 errorcode) {
    T0IF=0;
    T0IE=0;
    ir_operationmode = IR_WAIT_FOR_START;
    displayChar(errorcode);
}

bool ir_isInRange(uint8 units, uint8 time){
    return units - 3  < time && time < units + 3;
}

bool ir_fallingEdge(bool pin){
    return ir_pinstate_old && !pin;
}

bool ir_risingEdge(bool pin){
    return !ir_pinstate_old && pin;
}

void ir_interruptHandler(void) {
    bool current_pin;
    uint8 tdiff;
    
    /* get RC5 pin status */
    current_pin = RC5_DATA_PIN;
    
    if (current_pin == ir_pinstate_old) {
        return; //interrupt has not been called due to a change of our pin
    }
    
    /* calculate time difference to last interrupt call */
    tdiff = RC5_TIMER;
    
        
    if (ir_operationmode == IR_WAIT_FOR_START) {
        if (ir_fallingEdge(current_pin)) {
            T0IF=0;
            T0IE=1;//TMR0 Interrupt enabled
            
            ir_operationmode = IR_WAIT_FOR_START_HI;
            RC5_TIMER = 0;
        }
    } else if (ir_operationmode == IR_WAIT_FOR_START_HI) {
        if (ir_risingEdge(current_pin)) {
            if (ir_isInRange(IR_START_PERIOD_LO, tdiff )) {
                ir_operationmode = IR_WAIT_FOR_DATA;
                RC5_TIMER = 0;
                ir_temp_code = 0;
                ir_bit_pos = 13;
            }
        }
    } else if (ir_operationmode == IR_WAIT_FOR_DATA) {
        if (ir_fallingEdge(current_pin)) {
            if (ir_isInRange(IR_START_PERIOD_HI, tdiff)) {
                ir_operationmode = IR_IS_PAUSING;
                RC5_TIMER = 0;
            }
        }
    } else if (ir_operationmode == IR_IS_PAUSING) {
        if (ir_risingEdge(current_pin)) {
            if (ir_isInRange(IR_PAUSE, tdiff )) {
                ir_operationmode = IR_IS_READING_DATA;
                RC5_TIMER = 0;
            } else {
                ir_abort(0xE5);
            }
        } else {
            ir_abort(0xE6);
        }
    } else if (ir_operationmode == IR_IS_READING_DATA) {
        if (ir_fallingEdge(current_pin)) {
            if (ir_isInRange(IR_HIGH_BIT, tdiff)) {
                bit_set(ir_temp_code, ir_bit_pos);
                ir_bit_pos--;
                ir_operationmode = IR_IS_PAUSING;
                RC5_TIMER = 0;
                LED = 1;
            } else if (ir_isInRange(IR_LOW_BIT, tdiff)) {
                bit_clear(ir_temp_code, ir_bit_pos);
                ir_operationmode = IR_IS_PAUSING;
                RC5_TIMER = 0;
                ir_bit_pos--;
                LED = 0;
            } else {
                ir_abort(0xE7);
            }
        } else {
            ir_abort(0xE8);
        }
    }
   
    
    /* save current pin state for edge detection */
    ir_pinstate_old = current_pin;
    
}