
#include "GPIO_STM32F10x.h"
#include "cmsis_os2.h"

static osThreadId_t tid;
static GPIO_PIN_ID  led;
static uint32_t     ticks = 1000;

static void LED_Thread(void const *argument) {

  led.port = GPIOC;
  led.num = 13;
  
  GPIO_PortClock(led.port, true);
  GPIO_PinWrite(led.port, led.num, 0);
  GPIO_PinConfigure(led.port, led.num, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT2MHZ);

  while (1) {
    GPIO_PinWrite(led.port, led.num, 1);
    osDelay(ticks);
    GPIO_PinWrite(led.port, led.num, 0);
    osDelay(ticks);
  }
}

int LED_Init(void) {

  tid = osThreadNew(LED_Thread, NULL, NULL);
  if (!tid) {
    return -1;
  }

  return 0;
}
