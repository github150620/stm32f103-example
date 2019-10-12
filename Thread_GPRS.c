
#include "cmsis_os.h"
#include "USART_STM32F10x.h"

extern ARM_DRIVER_USART Driver_USART1;

void Thread_GPRS(void const *argument);
osThreadId tid_Thread_GPRS;
osThreadDef(Thread_GPRS, osPriorityNormal, 1, 0);

osMessageQId mqid_Thread_GPRS;
osMessageQDef(Thread_GPRS, 32, uint32_t);

int Init_Thread_GPRS(void) {
  tid_Thread_GPRS = osThreadCreate(osThread(Thread_GPRS), NULL);
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
    
  }
}
