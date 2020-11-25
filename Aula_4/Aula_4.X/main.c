//******************************************************************************
//---------- SEEV - 3ºano - EAUTO ----------------------------------------------
//---------- Programa base para Aula 3 -----------------------------------------
//---------- Pedro Martins / Luis Bento ----------------------------------------
//---------- ESTG / IPLeiria ---------------------------------------------------
//******************************************************************************

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"

#define constant_A 42

bool mode = false;
int pot_val, codigo_digital, pwm;

/*
                         Interruptions Services Routines
 */
void IOCB4_InterruptCall(void){
    //Add code for S1_interruption
}
void INT0_InterruptCall(void){
    
        mode = !mode;
        
}

void function_relay (void){
    codigo_digital=ADC_GetConversion(POT);
    pot_val=codigo_digital*0.02442002442;
    if(pot_val>42) RELAY_CTL_SetHigh();
    else RELAY_CTL_SetLow();
}

void function_pwm (void){
    pwm=10.23*pot_val; //PWM=(pot_val)/1023 (10 bits -> 2^9 = 1023)
    EPWM1_LoadDutyValue(pwm);
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    SPI_Open(SPI_DEFAULT);
    lcd_init();

    //Interrupt Callback Functions
    IOCB4_SetInterruptHandler(IOCB4_InterruptCall);
    INT0_SetInterruptHandler(INT0_InterruptCall);
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    while (1)
    {
        // Add your application code
        function_relay();
        function_pwm();
    }
}
/*
 End of File
*/