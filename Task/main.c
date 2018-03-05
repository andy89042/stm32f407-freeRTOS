#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx.h"

//Task1
// ----------------------------------------------------------------------------
void vTask1( void *pvParameters )
{
const char *pcTaskName = "Task 1 is running\r\n";
volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
/* As per most tasks, this task is implemented in an infinite loop. */
volatile uint16_t count1=0;
for( ;; )
{
/* Print out the name of this task. */
count1++;
/* Delay for a period. */
for( ul = 0; ul < 1000; ul++ )
{
/* This loop is just a very crude delay implementation. There is
nothing to do in here. Later examples will replace this crude
loop with a proper delay/sleep function. */
}
}
}

//Task2
// ----------------------------------------------------------------------------
void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task 2 is running\r\n";
volatile uint32_t ul; /* volatile to ensure ul is not optimized away. */
/* As per most tasks, this task is implemented in an infinite loop. */
volatile	uint16_t count2=0;
for( ;; )
{
/* Print out the name of this task. */
count2++;
/* Delay for a period. */
for( ul = 0; ul < 1000; ul++ )
{
/* This loop is just a very crude delay implementation. There is
nothing to do in here. Later examples will replace this crude
loop with a proper delay/sleep function. */
}
}
}


int main( void )
{
/* Create one of the two tasks. Note that a real application should check
the return value of the xTaskCreate() call to ensure the task was created
successfully. */
xTaskCreate( vTask1, /* Pointer to the function that implements the task. */
"Task 1",/* Text name for the task. This is to facilitate
debugging only. */
100, /* Stack depth - small microcontrollers will use much
less stack than this. */
NULL, /* This example does not use the task parameter. */
1, /* This task will run at priority 1. */
NULL ); /* This example does not use the task handle. */
/* Create the other task in exactly the same way and at the same priority. */
xTaskCreate( vTask2, "Task 2", 100, NULL, 2, NULL );
/* Start the scheduler so the tasks start executing. */
vTaskStartScheduler();
/* If all is well then main() will never reach here as the scheduler will
now be running the tasks. If main() does reach here then it is likely that
there was insufficient heap memory available for the idle task to be created.
Chapter 2 provides more information on heap memory management. */
for( ;; );
}

