#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"

int adc_value = 0, turn_on_value = 90, turn_off_value = 80;
long int adc_perc = 0;
char string[30] = "";

/*
                         Interrupt Functions
 */
void INTERRUPT_S1_CALLBACK(void) {
    if (INT_S1_PORT == 0) {
        printf("\f\rPOT: %3d \r", adc_perc);
        
        TMR0_WriteTimer(0x00);
        TMR0_StartTimer();
    }
    if (INT_S1_PORT == 1) {
        TMR0_StopTimer();
    }
}

int read_from_usart(int length) {
    char data[10];
    int value = 0;

    for (int i = 0; i < length; i++) {
        while (!PIR1bits.RC1IF);
        if (EUSART1_is_rx_ready()) {
            data[i] = EUSART1_Read();
            if (EUSART1_is_tx_ready()) {
                EUSART1_Write(data[i]);
                TMR0_WriteTimer(0x00);
            }
        }
    }
    value = atoi(data);
    return value;
}

/*
                         Main application
 */
void main(void) {
    int dummy;
    
    // Initialize the device
    SYSTEM_Initialize();
    SPI_Open(SPI_DEFAULT);
    lcd_init();

    // Flash all IO from Port B
    dummy=PORTB;
    INTCONbits.RBIF = 0;
    
    // Interrupt Callback functions
    IOCB4_SetInterruptHandler(INTERRUPT_S1_CALLBACK);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    lcd_draw_string(60, 220, "EAU          SEEV         AULA_5", WHITE, BLACK);
    TMR0_WriteTimer(0x00);

    while (1) {
        // Read and print POT value
        adc_value = ADC_GetConversion(POT_PIN);
        adc_perc = (long int) adc_value * 100 / 4095;
        snprintf(string, sizeof (string), "POT: %3d %%", adc_perc);
        lcd_draw_string(100, 100, string, WHITE, BLACK);

        // Toogle LED D3 with hysteresis
        if (adc_perc >= turn_on_value) {
            LED_D3_SetHigh();
        }
        if (adc_perc <= turn_off_value) {
            LED_D3_SetLow();
        }

        // Configuration Menu
        if (TMR0_ReadTimer() > 23500) {
            // Read turn ON and turn OFF value from keyboard
            printf("Configuration MODE \n\r");
            printf("\n\rACTUAL TURN VALUES  ON: %d OFF: %d\n\r", turn_on_value, turn_off_value);

            printf("\n\rTurn ON Value: \n\r");
            turn_on_value = read_from_usart(2);
            printf("\n\rTurn OFF Value: \n\r");
            turn_off_value = read_from_usart(2);

            printf("\n\n\rTURN VALUES SAVED   ON: %d OFF: %d\n\r", turn_on_value, turn_off_value);
        }
    }
}
/**
 End of File
 */