// Created: 2023-07-31
// Updated: 2023-08-01
// This got me familiar with the BeagleBone Black and wireless
// communication concepts.

/************************************Includes***************************************/

#include "G8RTOS/G8RTOS.h"
#include "./MultimodDrivers/multimod.h"

#include "./threads.h"

/************************************MAIN*******************************************/

int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    multimod_init();
    G8RTOS_Init();

    G8RTOS_InitSemaphore(&sem_SPIA, 1);
    G8RTOS_InitSemaphore(&sem_packetrdy, 0);

    G8RTOS_AddThread(DrawBoundingBox_Thread, 200, "Bounding\0");
    G8RTOS_AddThread(Idle_Thread, 255, "idle\0");

    G8RTOS_Add_APeriodicEvent(UART4_Handler, 5, 76);
    
    G8RTOS_Launch();
    while(1);
}

/************************************MAIN*******************************************/
