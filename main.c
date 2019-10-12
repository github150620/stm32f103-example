
#include "stm32f10x.h"
#include "cmsis_os.h"

//#include "GPIO_STM32F10x.h"
//#include "USART_STM32F10x.h"

int main(void) {
  osKernelInitialize();
  osKernelStart();  
  while (1) {
    osDelay(1000);
  }
}


