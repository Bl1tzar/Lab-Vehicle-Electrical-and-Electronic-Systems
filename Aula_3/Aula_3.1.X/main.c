//******************************************************************************
//---------- SEEV - 3ºano - EAUTO ----------------------------------------------
//---------- Programa base para Aula 3 -----------------------------------------
//---------- Pedro Martins / Luis Bento ----------------------------------------
//---------- ESTG / IPLeiria ---------------------------------------------------
//******************************************************************************

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"
int codigo_digit, botao=0;
float tensao_in, temp, pot_val, ntc_val, temp_ntc;
char string_temp[100], string_pot[100], string_ntc[100], string_ntc_low[100], string_ntc_high[100];


/*
                         Interruptions Services Routines
 */
void IOCB4_InterruptCall(void){
    //Add code for S1_interruption
    if(!S1_PORT){
//        LED4_Toggle();
        if(botao!=3){
            botao++;
        }
        else{
            botao=0;
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
        if (botao==1){
            codigo_digit=ADC_GetConversion(TEMP);
            tensao_in=codigo_digit*0.000805664063; //tensao=codigo_digital*(Vref/2^10) 
            temp=tensao_in*33.3333333;
            snprintf(string_temp,sizeof(string_temp),"Temp=%.f C      ",temp);
            lcd_draw_string(100,100,string_temp,WHITE,BLACK);
                if (temp >= 90){
                LED3_SetHigh();
            }
                else{
                LED3_SetLow();
            }
        }
        if (botao==0){
            codigo_digit=ADC_GetConversion(POT);
            pot_val=codigo_digit*0.0244200244200244;
            snprintf(string_pot,sizeof(string_pot),"Pot=%.f%%      ",pot_val);
            lcd_draw_string(100,100,string_pot,WHITE,BLACK);
        }
        if (botao==2){
            codigo_digit=ADC_GetConversion(NTC);
            tensao_in=codigo_digit*0.000805664063;
            ntc_val=((-1440*tensao_in)-12853.770491803)/(tensao_in-8.9262295081968); //Vo=(V+ - V-).G || V+ = 3,3 . (NTC/(NTC+R9))  -> NTC = ((-R9.Vo)-(R9.G.V-))/(Vo + G.(V- - 3,3))) 
            temp_ntc=(-ntc_val+4425.5)/(85.3);
            snprintf(string_ntc,sizeof(string_ntc),"NTC=%.f C            ",temp_ntc);
            lcd_draw_string(100,100,string_ntc,WHITE,BLACK);
                if (temp_ntc >= 30){
                LED4_SetHigh();
            }
                else{
                LED4_SetLow();
            }
                if (temp_ntc < 20){ 
                    snprintf(string_ntc_low,sizeof(string_ntc_low),"0FF           ");
                    lcd_draw_string(100,80,string_ntc_low,WHITE,BLACK);
            }
                if (temp_ntc > 30){
                    snprintf(string_ntc_high,sizeof(string_ntc_high),"1FF           ");
                    lcd_draw_string(100,80,string_ntc_high,WHITE,BLACK);
            }
        }
    }
}   
/*
 End of File
*/