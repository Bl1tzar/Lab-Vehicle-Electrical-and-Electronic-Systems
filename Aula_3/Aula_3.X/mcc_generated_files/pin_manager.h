/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F46K80
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set POT aliases
#define POT_TRIS                 TRISAbits.TRISA0
#define POT_LAT                  LATAbits.LATA0
#define POT_PORT                 PORTAbits.RA0
#define POT_ANS                  ANCON0bits.ANSEL0
#define POT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define POT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define POT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define POT_GetValue()           PORTAbits.RA0
#define POT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define POT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define POT_SetAnalogMode()      do { ANCON0bits.ANSEL0 = 1; } while(0)
#define POT_SetDigitalMode()     do { ANCON0bits.ANSEL0 = 0; } while(0)

// get/set LED3 aliases
#define LED3_TRIS                 TRISAbits.TRISA5
#define LED3_LAT                  LATAbits.LATA5
#define LED3_PORT                 PORTAbits.RA5
#define LED3_ANS                  ANCON0bits.ANSEL4
#define LED3_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED3_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED3_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED3_GetValue()           PORTAbits.RA5
#define LED3_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED3_SetAnalogMode()      do { ANCON0bits.ANSEL4 = 1; } while(0)
#define LED3_SetDigitalMode()     do { ANCON0bits.ANSEL4 = 0; } while(0)

// get/set LED4 aliases
#define LED4_TRIS                 TRISAbits.TRISA6
#define LED4_LAT                  LATAbits.LATA6
#define LED4_PORT                 PORTAbits.RA6
#define LED4_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define LED4_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define LED4_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define LED4_GetValue()           PORTAbits.RA6
#define LED4_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set LED5 aliases
#define LED5_TRIS                 TRISAbits.TRISA7
#define LED5_LAT                  LATAbits.LATA7
#define LED5_PORT                 PORTAbits.RA7
#define LED5_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LED5_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LED5_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LED5_GetValue()           PORTAbits.RA7
#define LED5_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LED5_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set S1 aliases
#define S1_TRIS                 TRISBbits.TRISB4
#define S1_LAT                  LATBbits.LATB4
#define S1_PORT                 PORTBbits.RB4
#define S1_WPU                  WPUBbits.WPUB4
#define S1_ANS                  ANCON1bits.ANSEL9
#define S1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define S1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define S1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define S1_GetValue()           PORTBbits.RB4
#define S1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define S1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define S1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define S1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define S1_SetAnalogMode()      do { ANCON1bits.ANSEL9 = 1; } while(0)
#define S1_SetDigitalMode()     do { ANCON1bits.ANSEL9 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

// get/set IO_RE0 aliases
#define IO_RE0_TRIS                 TRISEbits.TRISE0
#define IO_RE0_LAT                  LATEbits.LATE0
#define IO_RE0_PORT                 PORTEbits.RE0
#define IO_RE0_ANS                  ANCON0bits.ANSEL5
#define IO_RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define IO_RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define IO_RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define IO_RE0_GetValue()           PORTEbits.RE0
#define IO_RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define IO_RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define IO_RE0_SetAnalogMode()      do { ANCON0bits.ANSEL5 = 1; } while(0)
#define IO_RE0_SetDigitalMode()     do { ANCON0bits.ANSEL5 = 0; } while(0)

// get/set IO_RE1 aliases
#define IO_RE1_TRIS                 TRISEbits.TRISE1
#define IO_RE1_LAT                  LATEbits.LATE1
#define IO_RE1_PORT                 PORTEbits.RE1
#define IO_RE1_ANS                  ANCON0bits.ANSEL6
#define IO_RE1_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define IO_RE1_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define IO_RE1_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define IO_RE1_GetValue()           PORTEbits.RE1
#define IO_RE1_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define IO_RE1_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define IO_RE1_SetAnalogMode()      do { ANCON0bits.ANSEL6 = 1; } while(0)
#define IO_RE1_SetDigitalMode()     do { ANCON0bits.ANSEL6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCB4 pin functionality
 * @Example
    IOCB4_ISR();
 */
void IOCB4_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCB4 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCB4 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCB4_SetInterruptHandler(MyInterruptHandler);

*/
void IOCB4_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCB4 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCB4_SetInterruptHandler() method.
    This handler is called every time the IOCB4 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCB4_SetInterruptHandler(IOCB4_InterruptHandler);

*/
extern void (*IOCB4_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCB4 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCB4_SetInterruptHandler() method.
    This handler is called every time the IOCB4 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCB4_SetInterruptHandler(IOCB4_DefaultInterruptHandler);

*/
void IOCB4_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/