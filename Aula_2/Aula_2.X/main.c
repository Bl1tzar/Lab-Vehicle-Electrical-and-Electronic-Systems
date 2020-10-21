//********************************************************************************* 
//---------- SEEV - 3ºano - EAUTO -------------------------------------------------
//---------- Programa Base para Aula 2 --------------------------------------------
//---------- Pedro Martins / Luís Bento --------------------------------------
//---------- ESTG / IPLeiria ------------------------------------------------------
//********************************************************************************* 

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"
#include <stdio.h>


int codigo_digital;
uint16_t percentagem;
char string[100];

/*
                          Interrupt Services Routines
*/
// Add your interrupt function

void acende_led(void){
    if (S1_PORT == 0){
        LED3_Toggle();
        codigo_digital = ADC_GetConversion(POT); //Obter codigo digital do conversor ADC
    }
}

void ADC_POT (void){
    
    percentagem = 40;
    //percentagem = (4095/codigo_digital)*100 ;
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    IOCB4_SetInterruptHandler(acende_led);
    
    ADC_SetInterruptHandler(ADC_POT);
    
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
        //Confirmado
        snprintf(string,sizeof(string),"percentagem = %d",percentagem);
        lcd_draw_string (120,80,string,GREEN,BLACK);
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