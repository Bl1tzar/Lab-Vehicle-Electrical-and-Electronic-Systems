#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"

#define sign(a) ( ( (a) < 0 ) ? in -1 : ( (a) > 0 ) )

#define INT_ANTI_WINDUP 100

int turn_on_value = 20, turn_off_value = 10, KP = 140, sum_error = 0, Ki = 6;
float sensor = 0, setpoint = 0, error = 0;
float dc_value = 0;
char string[30] = "", Draw_Graph = 0;

//******************************************************************************
//--------------------------- Function USART_menu()-----------------------------

void Out_USART(void) {
    char value_1[3] = "";
    char value_2[2] = "";
    char value_3[4] = "";
    char lixo;
    
    while (EUSART1_is_rx_ready()) {
        lixo = EUSART1_Read(); //Read the previous character to remove it from buffer
    }

//    printf("\n\r ERROR ALARM Hysteresis \n\r Insert a new turn ON value between 00-99:");
//    value_1[0] = EUSART1_Read();
//    value_1[1] = EUSART1_Read();
//    turn_on_value = atoi(value_1);
//    printf("\n\rValue: %d", turn_on_value);
//
//    printf("\n\rInsert a new turn OFF value between 00-99:");
//    value_2[0] = EUSART1_Read();
//    value_2[1] = EUSART1_Read();
//    turn_off_value = atoi(value_2);
//    printf("\n\rValue: %d", turn_off_value);
//
//    printf("\n\rNew value are: %d  and %d", turn_on_value, turn_off_value);

    printf("\n\rInsert a new turn KP value between 00-99:");
    value_3[0] = EUSART1_Read();
    value_3[1] = EUSART1_Read();
    value_3[2] = EUSART1_Read();
    value_3[3] = EUSART1_Read();
    KP = atoi(value_3);
    printf("\n\rValue: %d", KP);
    
    printf("\n\rInsert a new turn Ki value between 00-99:");
    value_1[0] = EUSART1_Read();
    value_1[1] = EUSART1_Read();
    value_1[2] = EUSART1_Read();
    //value_1[3] = EUSART1_Read();
    Ki = atoi(value_1);
    printf("\n\rValue: %d", Ki);
    
}

//******************************************************************************
//--------------------------- Function Get_values ------------------------------

void Get_values(void) {
    setpoint = (long int) (ADC_GetConversion(POT_PIN)) * 100 / 4095;
    sensor = (long int) (ADC_GetConversion(SENSOR)) * 100 / 4095;
}

//******************************************************************************
//-------------------------- Function PI_Controller ----------------------------

void PI_Controller(void) {
    error = setpoint - sensor;
    sum_error = sum_error + error;
    
    if (abs(sum_error) > INT_ANTI_WINDUP)
        sum_error = INT_ANTI_WINDUP * sign(sum_error);
    
    dc_value = (error * KP / 10.0) + (sum_error*(Ki/10.0));

    if (dc_value > 100)
        dc_value = 100;
    else if (dc_value < 0)
        dc_value = 0;

    dc_value = (long int) dc_value * 10.23;

    EPWM1_LoadDutyValue(dc_value); //set the duty cycle [0 1023]

    // Toogle LED D3 with hysteresis
    if (abs(error) >= turn_on_value) {
        LED_D3_SetHigh();
    }
    if (abs(error) <= turn_off_value) {
        LED_D3_SetLow();
    }
}

/*
                         Interrupt Functions
 */
void INTERRUPT_S1_CALLBACK(void) {
    if (INT_S1_PORT == 0) {
        // Do something
    }
}

void TIMER2_CALLBACK(void) {
    Get_values();
    PI_Controller();
}

/*
                         Main application
 */
void main(void) {
    int dummy;

    // Initialize the device
    SYSTEM_Initialize();
    TMR2_StopTimer();

    SPI_Open(SPI_DEFAULT);
    lcd_init();


    // Flash all IO from Port B
    dummy = PORTB;
    INTCONbits.RBIF = 0;

    // Interrupt Callback functions
    IOCB4_SetInterruptHandler(INTERRUPT_S1_CALLBACK);
    TMR2_SetInterruptHandler(TIMER2_CALLBACK);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    lcd_draw_string(60, 220, "EAU          SEEV         AULA_6", WHITE, BLACK);
    snprintf(string, sizeof (string), "SETPOINT: SPT");
    lcd_draw_string(100, 180, string, WHITE, BLACK);
    snprintf(string, sizeof (string), "MOTOR:MTR");
    lcd_draw_string(100, 160, string, WHITE, BLACK);
    snprintf(string, sizeof (string), "ERROR:ERR");
    lcd_draw_string(100, 140, string, WHITE, BLACK);
    snprintf(string, sizeof (string), "DUTYCYCLE: DC");
    lcd_draw_string(100, 120, string, WHITE, BLACK);
    snprintf(string, sizeof (string), "SPT   MTR   ERR   DC", setpoint, sensor);
    lcd_draw_string(100, 50, string, WHITE, BLACK);

    TMR2_StartTimer();

    while (1) {

        if (EUSART1_is_rx_ready()) {
            Out_USART();
        }
        if (Draw_Graph == 1) {

        } else {
            snprintf(string, sizeof (string), "%03d%% %03d%% %03d%% %04d ", setpoint, sensor, error, dc_value);
            lcd_draw_string(100, 25, string, WHITE, BLACK);
        }
    }
}
/**
 End of File
 */