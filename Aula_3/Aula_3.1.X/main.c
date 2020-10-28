//******************************************************************************
//---------- SEEV - 3ºano - EAUTO ----------------------------------------------
//---------- Programa base para Aula 3 -----------------------------------------
//---------- Pedro Martins / Luis Bento ----------------------------------------
//---------- ESTG / IPLeiria ---------------------------------------------------
//******************************************************************************

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"

/*
                         Interruptions Services Routines
 */
void IOCB4_InterruptCall(void){
    //Add code for S1_interruption
    if(!S1_PORT){
        LED4_Toggle();
    }
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
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    lcd_draw_string(100,120,"HELLO WORLD",WHITE,BLACK);
    
    while (1)
    {
        // Add your application code
        
    }
}
/*
 End of File
*/