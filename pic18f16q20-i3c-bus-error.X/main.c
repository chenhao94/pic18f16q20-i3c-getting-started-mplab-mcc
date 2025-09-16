 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
? [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <string.h>

/*
    Main application
*/
void BusErrorCallback(void);
void HotJoinRequest(void);

volatile uint8_t busErrorStatus;
volatile uint8_t busErrorReceived;

int main(void)
{
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 
    
    //Register user callback for Bus error
    I3C_Target_BusErrorCallbackRegister(BusErrorCallback);

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    HotJoinRequest();
    printf("Waiting for dynamic address assignment\r\n");
    while(I3C1_OperatingModeGet() != I3C_TARGET_OPERATING_MODE_I3C_SDR);
    printf("Dynamic address is assigned\r\n");

    printf("I3C Bus Error Detection\r\n");
    
    while(1)
    {
        if(busErrorReceived)
        {
            busErrorReceived = false;

            if(busErrorStatus & I3C_TARGET_BUS_TE0_ERROR)
            {
                printf("TE0 bus error received\r\n");
            }

            if(busErrorStatus & I3C_TARGET_BUS_TE1_ERROR)
            {
                printf("TE1 bus error received\r\n");
            }

            if(busErrorStatus & I3C_TARGET_BUS_TE2_ERROR)
            {
                printf("TE2 bus error received\r\n");
            }

            if(busErrorStatus & I3C_TARGET_BUS_TE3_ERROR)
            {
                printf("TE3 bus error received\r\n");
            }

            if(busErrorStatus & I3C_TARGET_BUS_TE4_ERROR)
            {
                printf("TE4 bus error received\r\n");
            }

            if(busErrorStatus & I3C_TARGET_BUS_TE5_ERROR)
            {
                printf("TE5 bus error received\r\n");
            }

            if(busErrorStatus & I3C_TARGET_BUS_TE6_ERROR)
            {
                printf("TE6 bus error received\r\n");
            }
        }
    }
}

void BusErrorCallback(void)
{
    busErrorReceived = true;        
    busErrorStatus = I3C_Target_BusErrorStatusGetAndClear();
}

void HotJoinRequest(void)
{  
    enum I3C_TARGET_HJ_REQUEST_ERROR hJRequestError = I3C_TARGET_HJ_REQUEST_NO_ERROR;
    
	printf("Type 'send' to send Hot Join request\r\n");
	char input[10];
	while(1)
	{
		scanf("%s", input);
		if(strcmp(input, "send") == 0)
		{
			break;
		}
		else
		{
			printf("Invalid command '%s'. Type 'send' to send Hot Join request\r\n", input);
		}
	}
	printf("Command 'send' received\r\n\n");
    printf("Requesting the Hot Join\r\n");
    hJRequestError = I3C_Target_HotJoinRequest();

	if(hJRequestError == I3C_TARGET_HJ_REQUEST_NO_ERROR)
	{
		printf("HotJoinRequest: No error\r\n\n");
	}
	else if(hJRequestError == I3C_TARGET_HJ_REQUEST_NOT_HJ_CAPABLE)
	{
		printf("HotJoinRequest: Target is not HJ capable\r\n\n");
	}
	else if(hJRequestError == I3C_TARGET_HJ_REQUEST_DYNAMIC_ADDRESS_ALREADY_ASSIGNED)
	{
		printf("HotJoinRequest: Dynamic address has already been assigned\r\n\n");
	}
	else if(hJRequestError == I3C_TARGET_HJ_REQUEST_HJ_DISABLED_ON_BUS)
	{
		printf("HotJoinRequest: HJ is disabled on the bus\r\n\n");
	}

	printf("Waiting for dynamic address\r\n");
	//Wait for Hot Join to complete
	while(I3C_Target_HotJoinStatusGet() == I3C_TARGET_HJ_PENDING);
	printf("Hot-Join completed successfully with dynamic address = 0x%02X\r\n\n", I3C1DADR);
}
