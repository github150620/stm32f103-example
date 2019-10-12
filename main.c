
#include "stm32f10x.h"
#include "cmsis_os.h"

extern int Init_Thread_LED(void);
extern int Init_Thread_GPRS(void);

int main(void) {
  
  osKernelInitialize();
  
  Init_Thread_LED();
  Init_Thread_GPRS();
  
  osKernelStart();
  
  while (1) {
    osDelay(1000);
  }
}


