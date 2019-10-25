
#include "stm32f10x.h"
#include "cmsis_os2.h"

#include "log.h"

extern int LED_Init(void);
extern int GPRS_Init(void);

int main(void) {
  
  osKernelInitialize();
  
  LOG_Init();
  LED_Init();
  GPRS_Init();
  
  osKernelStart();
  
  while (1) {
    osDelay(1000);
  }
}


