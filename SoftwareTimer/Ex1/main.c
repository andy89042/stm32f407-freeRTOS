#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx.h"
#include "queue.h"
#include "timers.h"
uint32_t ulCallCount;
//Task1
static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
TickType_t xTimeNow;
/* Obtain the current tick count. */
xTimeNow = xTaskGetTickCount();
//output
GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
/* File scope variable. */
ulCallCount++;
}
//Task2
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
TickType_t xTimeNow;
/* Obtain the current tick count. */
xTimeNow = xTaskGetTickCount();
//output
GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
ulCallCount++;
}
//// ----------------------------------------------------------------------------
void GPIOInit(){
    GPIO_InitTypeDef g;
    g.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; // ?? 12,13,14,15 ?
    g.GPIO_Mode = GPIO_Mode_OUT; // ???????
    g.GPIO_Speed = GPIO_Speed_100MHz; // ?? GPIO ???100 MHz
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // ?? GPIOD
    GPIO_Init(GPIOD, &g); // ??? GPIO D
}


/* The periods assigned to the one-shot and auto-reload timers are 3.333 second and half a second respectively. */
#define mainONE_SHOT_TIMER_PERIOD pdMS_TO_TICKS( 3333 )
#define mainAUTO_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 500 )
int main( void )
{
GPIOInit();	
TimerHandle_t xAutoReloadTimer, xOneShotTimer;
BaseType_t xTimer1Started, xTimer2Started;
/* Create the one shot timer, storing the handle to the created timer in xOneShotTimer. */
xOneShotTimer = xTimerCreate(
/* Text name for the software timer - not used by FreeRTOS. */
"OneShot",
/* The software timer's period in ticks. */
mainONE_SHOT_TIMER_PERIOD,
/* Setting uxAutoRealod to pdFALSE creates a one-shot software timer. */
pdFALSE,
/* This example does not use the timer id. */
0,
/* The callback function to be used by the software timer being created. */
prvOneShotTimerCallback );
/* Create the auto-reload timer, storing the handle to the created timer in xAutoReloadTimer. */
xAutoReloadTimer = xTimerCreate(
/* Text name for the software timer - not used by FreeRTOS. */
"AutoReload",
/* The software timer's period in ticks. */
mainAUTO_RELOAD_TIMER_PERIOD,
/* Setting uxAutoRealod to pdTRUE creates an auto-reload timer. */
pdTRUE,
/* This example does not use the timer id. */
0,
/* The callback function to be used by the software timer being created. */
prvAutoReloadTimerCallback );
/* Check the software timers were created. */
if( ( xOneShotTimer != NULL ) && ( xAutoReloadTimer != NULL ) )
{
/* Start the software timers, using a block time of 0 (no block time). The scheduler has
not been started yet so any block time specified here would be ignored anyway. */
xTimer1Started = xTimerStart( xOneShotTimer, 0 );
xTimer2Started = xTimerStart( xAutoReloadTimer, 0 );
/* The implementation of xTimerStart() uses the timer command queue, and xTimerStart()
will fail if the timer command queue gets full. The timer service task does not get
created until the scheduler is started, so all commands sent to the command queue will
stay in the queue until after the scheduler has been started. Check both calls to
xTimerStart() passed. */
if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
{
/* Start the scheduler. */
vTaskStartScheduler();
}
}
/* As always, this line should not be reached. */
for( ;; );
}
