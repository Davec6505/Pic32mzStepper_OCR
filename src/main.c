/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "../Pic32mzStepper_OCR.X/speed_control.h"

void CORETIMER_Fp(uint32_t status, uintptr_t context){
    
    LED1_Toggle();
}


void OCMP_Fp (uintptr_t context){
    LED2_Toggle();
}
// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    //uint16_t tmr_pr2 = 6249U;
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    CORETIMER_CallbackSet ( CORETIMER_Fp, 0);
    CORETIMER_Start();
    
   // OCMP4_CallbackRegister(OCMP_Fp,0);
    speed_cntr_Init_Timer1();
    OCMP4_Enable(); 
    TMR2_Start();
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        if(!SW1_Get()){
           speed_cntr_Move(10000, 10, 10, 500);
        }
        
        if(!SW2_Get()){
            speed_cntr_Move(-10000, 10, 10, 500);
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

