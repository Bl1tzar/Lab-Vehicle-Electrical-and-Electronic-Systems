//******************************************************************************
//---------- SEEV - 3ºano - EAUTO ----------------------------------------------
//---------- Programa base para Aula 3 -----------------------------------------
//---------- Pedro Martins / Luis Bento ----------------------------------------
//---------- ESTG / IPLeiria ---------------------------------------------------
//******************************************************************************

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"

int BUT_COMUT=0;
int code_digit;
int POT;
char sPOT[100];

/*
                         Interruptions Services Routines
 */
void IOCB4_InterruptCall(void){
    //Add code for S1_interruption
    if(!S1_PORT){ //! -> Logica NOT. E verdadeiro quando S1_PORT esta a 0
        LED4_Toggle();
        if(!BUT_COMUT){
            code_digit=ADC_GetConversion();
            BUT_COMUT=1;
        }
        else{
            BUT_COMUT=0;
            LED3_SetLow();
            lcd_draw_string();
        }
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
        if(BUT_COMUT){
            POT=code_digit*0.0244200244200244;
            snprintf(sPOT,sizeof(sPOT),"POT %d%%",POT);
            lcd_draw_string();
            if (POT>=95){
                LED3_SetHigh();
            }
        }
    }
}
/*
 End of File
*/