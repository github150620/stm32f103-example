
#include "USART_STM32F10x.h"
#include "cmsis_os2.h"

extern ARM_DRIVER_USART Driver_USART1;

void Thread_GPRS(void const *argument);

osThreadId_t tid_Thread_GPRS;
osMessageQueueId_t mqid_Thread_GPRS;

int Init_Thread_GPRS(void) {
  tid_Thread_GPRS = osThreadNew(Thread_GPRS, NULL, NULL);
  if (!tid_Thread_GPRS) {
    return -1;
  }
  return 0;
}

static void USART1_Callback(uint32_t event) {
  if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
  
  } else if (event & ARM_USART_EVENT_RX_TIMEOUT) {
  
  } else if(event & ARM_USART_EVENT_SEND_COMPLETE) {
  
  }
}

void Thread_GPRS(void const *argument) {

  osEvent event;

  mqid_Thread_GPRS = osMessageCreate(osMessageQ(Thread_GPRS), tid_Thread_GPRS);
  if (!mqid_Thread_GPRS) {
    return;
  }

  Driver_USART1.Initialize(USART1_Callback);
  Driver_USART1.PowerControl(ARM_POWER_FULL);
  Driver_USART1.Control(ARM_USART_MODE_ASYNCHRONOUS |
                        ARM_USART_DATA_BITS_8 |
                        ARM_USART_PARITY_NONE |
                        ARM_USART_STOP_BITS_1 |
                        ARM_USART_FLOW_CONTROL_NONE, 
                        115200);
  Driver_USART1.Control(ARM_USART_CONTROL_TX, 1);
  Driver_USART1.Control(ARM_USART_CONTROL_RX, 1);

  while (1) {
    event = osMessageGet(mqid_Thread_GPRS, osWaitForever);
    if (event.status == osOK) {
      
    }
  }
}
