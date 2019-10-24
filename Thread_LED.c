
#include "GPIO_STM32F10x.h"
#include "cmsis_os2.h"

static osThreadId_t tid;

void Thread_LED(void const *argument) {

  GPIO_PIN_ID led;
  led.port = GPIOC;
  led.num = 13;
  
  GPIO_PortClock(led.port, true);
  GPIO_PinWrite(led.port, led.num, 0);
  GPIO_PinConfigure(led.port, led.num, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT2MHZ);

  while (1) {
    GPIO_PinWrite(led.port, led.num, 1);
    osDelay(1000);
    GPIO_PinWrite(led.port, led.num, 0);
    osDelay(1000);
  }
}

int Init_Thread_LED(void) {

  tid = osThreadNew(Thread_LED, NULL, NULL);
  if (!tid) {
    return -1;
  }

  return 0;
}
