//******************************************************************************
//---------- SEEV - 3ºano - EAUTO ----------------------------------------------
//---------- Programa base para Aula 3 -----------------------------------------
//---------- Pedro Martins / Luis Bento ----------------------------------------
//---------- ESTG / IPLeiria ---------------------------------------------------
//******************************************************************************

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"

#define constant_A 42
#define constant_B 30

bool mode = false;
int pot_val, codigo_digital, pwm, menu=1, clean=0;
char lcd_pot[100],lcd_const_A[100],lcd_const_B[100];

/*
                         Interruptions Services Routines
 */
void IOCB4_InterruptCall(void){
    if(S1_PORT==0){
        if (menu==3){
            menu=1;
            clean=1;
        }
        else{
            clean=1;
            menu++;
        }
    }
}
void INT0_InterruptCall(void){   
        if (menu==3){
            menu=1;
            clean=1;
        }
        else{
            clean=1;
            menu++;
        }     
}

void function_relay (void){
    codigo_digital=ADC_GetConversion(POT);
    pot_val=codigo_digital*0.02442002442;
    if(pot_val>constant_A) RELAY_CTL_SetHigh();
    if (pot_val<constant_B) RELAY_CTL_SetLow();
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
    
    LED5_LAT=0;
    
    while (1)
    {
        // Add your application code
        function_relay();
        function_pwm();
        switch(menu){
             
             case 1:
                 if(clean==1){
                 lcd_fill_rect(80,70,300,150,BLACK);
                 }
                 clean=0;
                //mostrar no lcd o valor do POT
                sprintf(lcd_pot,"POT: %d%%",pot_val);
                lcd_draw_string (130,120,lcd_pot,AQUA,BLACK);
                
                LED3_LAT=0;
                LED4_LAT=0;
                
                 break;
             
             case 2:
                 if(clean==1){
                 lcd_fill_rect(80,70,300,150,BLACK);
                 }
                 clean=0;
                //mostrar no lcd o valor do POT
                sprintf(lcd_const_A,"CONSTANTE_A: %d",constant_A);
                lcd_draw_string (95,120,lcd_const_A,AQUA,BLACK);
                
                LED3_LAT=1;
                LED4_LAT=0;
                 
                 break;
                 
             case 3:
                 if(clean==1){
                 lcd_fill_rect(80,70,300,150,BLACK);
                 }
                 clean=0;
                //mostrar no lcd o valor do POT
                sprintf(lcd_const_B,"CONSTANTE_B: %d",constant_B);
                lcd_draw_string (95,120,lcd_const_B,AQUA,BLACK);
                
                LED3_LAT=0;
                LED4_LAT=1;
                
                 
                 menu=0;
                 break;
        }
    }
}
/*
 End of File
*/