#include "USART_STM32F10x.h"
#include "cmsis_os2.h"

#define TX_BUFFER_SIZE 80

extern ARM_DRIVER_USART Driver_USART3;

static osThreadId_t       tid;
static osMessageQueueId_t mqid;
static ARM_DRIVER_USART*  usart;

static char txBuffer[TX_BUFFER_SIZE];

static void USART_Callback(uint32_t event) {
  if(event & ARM_USART_EVENT_SEND_COMPLETE) {
  }
}

static void LOG_Thread(void *argument) {
  osStatus_t status;
	
  mqid = osMessageQueueNew(5, TX_BUFFER_SIZE, NULL);
  if (!mqid) {
		ticks = 100;
    return;
  }

  usart = &Driver_USART3;
  usart->Initialize(USART_Callback);
  usart->PowerControl(ARM_POWER_FULL);
  usart->Control(ARM_USART_MODE_ASYNCHRONOUS |
                        ARM_USART_DATA_BITS_8 |
                        ARM_USART_PARITY_NONE |
                        ARM_USART_STOP_BITS_1 |
                        ARM_USART_FLOW_CONTROL_NONE, 
                        115200);
  usart->Control(ARM_USART_CONTROL_TX, 1);
	
  while (1) {
    while (usart->GetStatus().tx_busy == 1) {
      osDelay(1);
    }
    status = osMessageQueueGet(mqid, txBuffer, NULL, osWaitForever);
    if (status == osOK) {	
      usart->Send(txBuffer, strlen(txBuffer));
    } else {
      usart->Send("[ERROR] osMessageQueueGet() returns error.\n", 63);
    }
  }
}

int LOG_Init(void) {
  tid = osThreadNew(LOG_Thread, NULL, NULL);
  if (!tid) {
    return -1;
  }
  return 0;
}

void LOG_Print(char *content) {
	osMessageQueuePut(mqid, content, 0, 0);
	osDelay(1);
}
