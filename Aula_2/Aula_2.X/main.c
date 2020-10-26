//********************************************************************************* 
//---------- SEEV - 3ºano - EAUTO -------------------------------------------------
//---------- Programa Base para Aula 2 --------------------------------------------
//---------- Pedro Martins / Luís Bento --------------------------------------
//---------- ESTG / IPLeiria ------------------------------------------------------
//********************************************************************************* 

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"
#include <stdio.h>


uint16_t codigo_digital;
float percentagem;
char string[100];
uint16_t ticks;
uint16_t rpm;
char string_rpm[100];
/*
                          Interrupt Services Routines
*/
// Add your interrupt function

void acende_led(void){
    if (S1_PORT == 0){
        LED3_Toggle();
        codigo_digital = ADC_GetConversion(POT); //Obter codigo digital do conversor ADC
        percentagem = codigo_digital*0.0244200244200244;
    }
}

void pulso_encoder(void){
    TMR0_StopTimer();
    ticks=TMR0_ReadTimer();
    TMR0_WriteTimer(0x00);
    TMR0_StartTimer();
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device 
    SYSTEM_Initialize(); //Inclui Timer_0 Initialize 

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:
    
    IOCB4_SetInterruptHandler(acende_led);
    INT0_SetInterruptHandler(pulso_encoder);
    SPI_Open(SPI_DEFAULT);
    
    lcd_init ();

    lcd_draw_line(40,150,280,150,YELLOW);
    
    lcd_draw_string (45,155,"XC8 - Biblioteca - LCD - ILI9341",BLUE,BLACK);
    
    lcd_draw_string (120,120,"PIC - SEEV",GREEN,BLACK);
    

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
        rpm=4687500/ticks;
        snprintf(string_rpm,sizeof(string_rpm),"RPM= %d      ",rpm);
        lcd_draw_string (10,80,string_rpm,GREEN,BLACK);

        snprintf(string,sizeof(string),"percentagem = %.f  ",percentagem);
        lcd_draw_string (150,80,string,GREEN,BLACK);
        // Add your application code
//        if(S1_PORT==0){
//            LED3_SetHigh();
//        }
//        else{
//            LED3_SetLow();
//        }
    }
}
/*
 End of File
*/