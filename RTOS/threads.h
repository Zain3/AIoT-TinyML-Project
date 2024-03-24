// threads.h
// Date Created: 2023-07-26
// Date Updated: 2023-07-26
// Threads

#ifndef THREADS_H_
#define THREADS_H_

/************************************Includes***************************************/

#include "./G8RTOS/G8RTOS.h"

/************************************Includes***************************************/

/*************************************Defines***************************************/

/*************************************Defines***************************************/

/***********************************Semaphores**************************************/

semaphore_t sem_I2CA;
semaphore_t sem_SPIA;
semaphore_t sem_packetrdy;
semaphore_t sem_Joystick_Debounce;
semaphore_t sem_KillCube;
semaphore_t sem_UART;

/***********************************Semaphores**************************************/

/***********************************Structures**************************************/

typedef struct __attribute__((__packed__)) BoundingBox_Packet {
    uint8_t header;
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t frame_width;
    uint16_t frame_height;
    uint8_t footer;
} BoundingBox_Packet_t;

/***********************************Structures**************************************/


/*******************************Background Threads**********************************/

void Idle_Thread(void);

void DrawBoundingBox_Thread(void);

/*******************************Background Threads**********************************/

/********************************Periodic Threads***********************************/

/********************************Periodic Threads***********************************/

/*******************************Aperiodic Threads***********************************/

void UART4_Handler(void);

/*******************************Aperiodic Threads***********************************/


#endif /* THREADS_H_ */

