/*
 *
 */

#include "USART_STM32F10x.h"
#include "cmsis_os2.h"

#include "log.h"

#define RX_BUFFER_SIZE 128
#define TX_BUFFER_SIZE 32

extern ARM_DRIVER_USART Driver_USART1;

static osThreadId_t       tid;
static osMessageQueueId_t mqid;
static osTimerId_t        tmid;
static ARM_DRIVER_USART*  usart;

static uint8_t rxBuffer[RX_BUFFER_SIZE];
static uint8_t txBuffer[TX_BUFFER_SIZE];
static char    msg[RX_BUFFER_SIZE];

static void USART_Callback(uint32_t event) {
  if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
  }

  if(event & ARM_USART_EVENT_SEND_COMPLETE) {
  }

  if(event & ARM_USART_EVENT_TX_UNDERFLOW) {
    LOG_Print("ARM_USART_EVENT_TX_UNDERFLOW\n");
  }

  if(event & ARM_USART_EVENT_RX_OVERFLOW) {
    LOG_Print("ARM_USART_EVENT_RX_OVERFLOW\n");
    usart->Control(ARM_USART_ABORT_RECEIVE, 1);
    usart->Receive(rxBuffer, sizeof(rxBuffer));
  }

  if (event & ARM_USART_EVENT_RX_TIMEOUT) {
    usart->Control(ARM_USART_ABORT_RECEIVE, 1);
    rxBuffer[usart->GetRxCount()] = '\0';
    osMessageQueuePut(mqid, rxBuffer, 0, 0);
    usart->Receive(rxBuffer, sizeof(rxBuffer));
  }

  if(event & ARM_USART_EVENT_RX_BREAK) {
    LOG_Print("ARM_USART_EVENT_RX_BREAK\n");
  }

  if(event & ARM_USART_EVENT_RX_FRAMING_ERROR) {
    LOG_Print("ARM_USART_EVENT_RX_FRAMING_ERROR\n");
  }

  if(event & ARM_USART_EVENT_RX_PARITY_ERROR) {
    LOG_Print("ARM_USART_EVENT_RX_PARITY_ERROR\n");
  }
}

static void Timer_Callback(void *argument) {

}

static void GPRS_Handler(char *msg) {

}

static void GPRS_Thread(void *argument) {
  osStatus_t status;

  usart = &Driver_USART1;
  usart->Initialize(USART_Callback);
  usart->PowerControl(ARM_POWER_FULL);
  usart->Control(ARM_USART_MODE_ASYNCHRONOUS |
                 ARM_USART_DATA_BITS_8 |
                 ARM_USART_PARITY_NONE |
                 ARM_USART_STOP_BITS_1 |
                 ARM_USART_FLOW_CONTROL_NONE, 
                 115200);
  usart->Control(ARM_USART_CONTROL_TX, 1);
  usart->Control(ARM_USART_CONTROL_RX, 1);

  osTimerStart(tmid, 1000);

  while (1) {
    status = osMessageQueueGet(mqid, msg, NULL, osWaitForever);
    if (status == osOK) {
      GPRS_Handler(msg);
    }
  }
}

int GPRS_Init(void) {

  mqid = osMessageQueueNew(4, RX_BUFFER_SIZE, NULL);
  if (!mqid) {
    return -1;
  }

  tmid = osTimerNew(Timer_Callback, osTimerOnce, NULL, NULL);
  if (!tmid_) {
    return -1;
  }

  tid = osThreadNew(GPRS_Thread, NULL, NULL);
  if (!tid) {
    return -1;
  }

  return 0;
}

int GPRS_Send(uint8_t *buf, uint8_t len) {
  
}
