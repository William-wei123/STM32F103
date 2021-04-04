/**
  ******************************************************************************
  * @file    xxx.c 
  * @author  Waveshare Team
  * @version 
  * @date    xx-xx-2014
  * @brief   xxxxx.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Config.h"
#include "LIB_Config.h"
#include "i2c_soft.h"
#include "spi_hard.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//#define PLL_SOURCE_HSI        // HSI (~8 MHz) used to clock the PLL, and the PLL is used as system clock source
                                //When the HSI is used as a PLL clock input, the maximum system clock
                                //frequency that can be achieved is 48 MHz.
#define PLL_SOURCE_HSE          // HSE (8MHz) used to clock the PLL, and the PLL is used as system clock source

//#define PLL_SOURCE_HSE_BYPASS // HSE bypassed with an external clock (8MHz, coming from ) used to clock


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void device_init(void);
static void driver_init(void);
static void system_clock_set(void);
static void system_tick_init(void);
static void usart2_Init(uint32_t wBaudrate);
static void port_init(void);

/* Private functions ---------------------------------------------------------*/


/**
  * @brief  System initialization.
  * @param  None
  * @retval  None
  */
void system_init(void)
{
	disable_irq();
	
    device_init();
    driver_init();
	
	enable_irq();
}

/**
 * @brief 
 * @param 
 * @retval 
 */
static void device_init(void)
{
	system_clock_set();
	system_tick_init();
	port_init();
	usart2_Init(115200); 
}

/**
  * @brief  driver initialization.
  * @param  None
  * @retval None
  */
static void driver_init(void)
{

}

static void system_clock_set(void)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;

	/* Reset the RCC clock configuration to the default reset state(for debug purpose) */
	/* Set HSION bit */
	RCC->CR |= (uint32_t)0x00000001;

	/* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */

	RCC->CFGR &= (uint32_t)0xF0FF0000;   

	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t)0xFEF6FFFF;

	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t)0xFFFBFFFF;

	/* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	RCC->CFGR &= (uint32_t)0xFF80FFFF;
	/* Disable all interrupts and clear pending bits  */
	RCC->CIR = 0x009F0000;

#ifdef DATA_IN_ExtSRAM
	SystemInit_ExtMemCtl(); 
#endif /* DATA_IN_ExtSRAM */

#ifdef PLL_SOURCE_HSI  
	/* At this stage the HSI is already enabled */
	/*  PLL configuration: PLLCLK = HSI/2 * 16 = 64 MHz */
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL));
	RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLMULL16);

#else /* PLL_SOURCE_HSE_BYPASS or PLL_SOURCE_HSE */  
	/* Enable HSE */    
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
	
#ifdef PLL_SOURCE_HSE_BYPASS
	RCC->CR |= ((uint32_t)RCC_CR_HSEBYP);
	
#endif   /* PLL_SOURCE_HSE_BYPASS */

	/* Wait till HSE is ready and if Time out is reached exit */
	do {
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;  
	} while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
		HSEStatus = (uint32_t)0x01;
	} else {
		HSEStatus = (uint32_t)0x00;
	}  

	if (HSEStatus == (uint32_t)0x01) {    
		/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
		                                RCC_CFGR_PLLMULL));
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
	} else{ 
		/* If HSE fails to start-up, the application will have wrong clock 
		configuration. User can add here some code to deal with this error */
	}

#endif /*PLL_SOURCE_HSI*/

	/* Enable Prefetch Buffer */
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	/* Flash 2 wait state */
	FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
	FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    


	/* HCLK = SYSCLK */
	RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

	/* PCLK2 = HCLK */
	RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

	/* PCLK1 = HCLK */
	RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

	/* Enable PLL */
	RCC->CR |= RCC_CR_PLLON;

	/* Wait till PLL is ready */
	while((RCC->CR & RCC_CR_PLLRDY) == 0)
	{
	}

	/* Select PLL as system clock source */
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

	/* Wait till PLL is used as system clock source */
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08){
	
	}

	SystemCoreClockUpdate();
}

/**
  * @brief  Initialize and start the system stick timer and its interrupt.
  * @param  None
  * @retval None
  */
static void system_tick_init(void)
{
	RCC_ClocksTypeDef tRCC;
	
	RCC_GetClocksFreq(&tRCC);  
	delay_init(tRCC.HCLK_Frequency);
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	;
}

/**
  * @brief  Initializes the PORT.
  * @param  None
  * @retval None
  */
static void port_init(void) 
{
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);   
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //disable JTAG and release PB3 PB4 PA15 !!!
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	GPIO_InitTypeDef tGPIO;
	/*----------------------------------------------------------------------------------*/
	//USART
	tGPIO.GPIO_Pin = GPIO_Pin_2;
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &tGPIO);  
	
	tGPIO.GPIO_Pin = GPIO_Pin_3;
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &tGPIO);
	/*----------------------------------------------------------------------------------*/

}

/**
  * @brief  Initializes the USARTx.
  * @param  None
  * @retval None
  */
static void usart2_Init(uint32_t wBaudrate)
{
   /* USARTx configured as follow:
        - BaudRate =  Baudrate
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
        */

	USART_InitTypeDef tUSART;
	//NVIC_InitTypeDef NVIC_InitStructure;

	/* config USART2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART2 mode config */
	tUSART.USART_BaudRate = wBaudrate;
	tUSART.USART_WordLength = USART_WordLength_8b;
	tUSART.USART_StopBits = USART_StopBits_1;
	tUSART.USART_Parity = USART_Parity_No;
	tUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		
	tUSART.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART2, &tUSART);
	
	USART_Cmd(USART2, ENABLE);
}


/*-------------------------------END OF FILE-------------------------------*/
