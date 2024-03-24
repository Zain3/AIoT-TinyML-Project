// G8RTOS_Threads.c
// Date Created: 2023-07-25
// Date Updated: 2023-07-27
// Defines for thread functions.

/************************************Includes***************************************/

#include "./threads.h"

#include "./MultimodDrivers/multimod.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************************************Includes***************************************/

/*************************************Defines***************************************/


/*************************************Defines***************************************/

/*********************************Global Variables**********************************/

BoundingBox_Packet_t packet;

/*********************************Global Variables**********************************/

/*************************************Threads***************************************/

void Idle_Thread(void) {
    while(1);
}

void DrawBoundingBox_Thread(void) {
    SysCtlDelay(1);
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t w = 0;
    uint16_t h = 0;


    //BoundingBox_Packet_t packet;

    while(1) {
        G8RTOS_WaitSemaphore(&sem_packetrdy);

        G8RTOS_WaitSemaphore(&sem_SPIA);
        ST7789_DrawLine(x, y, x, y + h, 0x0000);
        ST7789_DrawLine(x, y + h, x + w, y + h, 0x0000);
        ST7789_DrawLine(x + w, y + h, x + w, y, 0x0000);
        ST7789_DrawLine(x + w, y, x, y, 0x0000);
        G8RTOS_SignalSemaphore(&sem_SPIA);

        if (packet.header == 'I' && packet.footer == 'i') {
            x = packet.x / ((float) packet.frame_width) * X_MAX;
            y = packet.y / ((float) packet.frame_height) * Y_MAX;
            w = packet.w / ((float) packet.frame_width) * X_MAX;
            h = packet.h / ((float) packet.frame_width) * Y_MAX;

            G8RTOS_WaitSemaphore(&sem_SPIA);
            ST7789_DrawLine(x, y, x, y + h, ST7789_GREEN);
            ST7789_DrawLine(x, y + h, x + w, y + h, ST7789_GREEN);
            ST7789_DrawLine(x + w, y + h, x + w, y, ST7789_GREEN);
            ST7789_DrawLine(x + w, y, x, y, ST7789_GREEN);
            G8RTOS_SignalSemaphore(&sem_SPIA);
        }

        sleep(200);
    }
}

/********************************Periodic Threads***********************************/


/********************************Periodic Threads***********************************/


/*******************************Aperiodic Threads***********************************/

void UART4_Handler() {

    uint8_t* ptr = (uint8_t*) &packet;
    char c;
    uint32_t ui32Status = UARTIntStatus(UART4_BASE, true); // Get interrupt status

    while(UARTCharsAvail(UART4_BASE))
    {
        c = UARTCharGetNonBlocking(UART4_BASE);
        *(ptr++) = c;
    }

    G8RTOS_SignalSemaphore(&sem_packetrdy);

    // if header != I, footer != i, flush buffer
    UARTIntClear(UART4_BASE, ui32Status); // Clear the asserted interrupts
}


/*******************************Aperiodic Threads***********************************/
