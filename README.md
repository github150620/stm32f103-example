# stm32f103-example
STM32F103 example based on CMSIS-RTOS2.

## How to use
### Create project
Create a new project by MDK, and make GPIO USART and CMSIS-RTOS2 checked. 

### Add files
Copy ```*.c``` and ```*.h``` to your MDK project.

### Modify config
Modify file ```RTE/Device/STM32F103xx/RTE_Device.h```.
```
#define RTE_USART1                       1
...
#define RTE_USART1_TX_PORT_ID_DEF       1
...
#define RTE_USART1_RX_PORT_ID_DEF       1
...
#define RTE_USART2                       1
...
#define RTE_USART2_TX_PORT_ID_DEF       1
...
#define RTE_USART2_RX_PORT_ID_DEF       1
...
#define RTE_USART3                       1
...
#define RTE_USART3_TX_PORT_ID_DEF       1
...
#define RTE_USART3_RX_PORT_ID_DEF       1
...
```
