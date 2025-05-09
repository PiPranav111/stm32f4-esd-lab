
#include "main.h"
#include "stm32f4xx_hal.h"


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void lcd_enable(void);
void lcd_data(unsigned char);
void lcd_cmd(unsigned char);
void lcd_init(void);
void lcd_clear(void);
void lcd_displayString(int,int,unsigned char*);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

	unsigned char str1[] = "WELCOME";
	unsigned char str2[] = " PICT";

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();


  lcd_init();
  lcd_clear();
  lcd_displayString(1,0,str1);
  lcd_displayString(2,0,str2);
}

void lcd_data(unsigned char data)
{
	//RS=1 FOR LCD DATA
	GPIOD ->BSRR = (1<<10);

	GPIOE->BSRR = (data & 0x01) ? (1<<11) : ((uint32_t) (1<<11)<<16);
	GPIOE->BSRR = (data & 0x02) ? (1<<12) : ((uint32_t) (1<<12)<<16);
	GPIOE->BSRR = (data & 0x04) ? (1<<13) : ((uint32_t) (1<<13)<<16);
	GPIOE->BSRR = (data & 0x08) ? (1<<14) : ((uint32_t) (1<<14)<<16);
	GPIOE->BSRR = (data & 0x10) ? (1<<15) : ((uint32_t) (1<<15)<<16);
	GPIOD->BSRR = (data & 0x20) ? (1<<7) : ((uint32_t) (1<<7)<<16);
	GPIOD->BSRR = (data & 0x40) ? (1<<8) : ((uint32_t) (1<<8)<<16);
	GPIOD->BSRR = (data & 0x80) ? (1<<9) : ((uint32_t) (1<<9)<<16);

}

void lcd_cmd(unsigned char cmd)
{
	//RS=0 FOR LCD CMD
	GPIOD ->BSRR = (1<<10)<<16;

	GPIOE->BSRR = (cmd & 0x01) ? (1<<11) : ((uint32_t) (1<<11)<<16);
	GPIOE->BSRR = (cmd & 0x02) ? (1<<12) : ((uint32_t) (1<<12)<<16);
	GPIOE->BSRR = (cmd & 0x04) ? (1<<13) : ((uint32_t) (1<<13)<<16);
	GPIOE->BSRR = (cmd & 0x08) ? (1<<14) : ((uint32_t) (1<<14)<<16);
	GPIOE->BSRR = (cmd & 0x10) ? (1<<15) : ((uint32_t) (1<<15)<<16);
	GPIOD->BSRR = (cmd & 0x20) ? (1<<7) : ((uint32_t) (1<<7)<<16);
	GPIOD->BSRR = (cmd & 0x40) ? (1<<8) : ((uint32_t) (1<<8)<<16);
	GPIOD->BSRR = (cmd & 0x80) ? (1<<9) : ((uint32_t) (1<<9)<<16);

}


void lcd_enable(void)
{
	GPIOH ->BSRR = (1<<1);
	HAL_Delay(1);
	GPIOH ->BSRR = (1<<1)<<16;
	HAL_Delay(1);

}

void lcd_init(void)
{
	//RESET GPIO PH1
	GPIOH->BSRR=(1<<1)<<16;
	//RESET ALL THE PINS OF PORT E WHICH ARE IN USE
	GPIOE->BSRR = ((1<<11)|(1<<12)|(1<<13)|(1<<14)|(1<<15))<<16;
	//RESET ALL THE PINS OF PORT D WHICH ARE IN USE
	GPIOD->BSRR = ((1<<7)|(1<<8)|(1<<9))<<16;
	//5 LCD INIT COMMANDS
	/*
	 * 00111000 = 0x38
	 * 00000110 = 0x06
	 * 00001100 = 0x0C
	 * 00000001 = 0x01
	 * 10000000 = 0x80
	 */
	lcd_cmd(0x38);
	lcd_cmd(0x06);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
}

void lcd_clear(void)
{
	HAL_Delay(1);
	lcd_cmd(0x01);
	HAL_Delay(1);
}

void lcd_displayString(int row, int pos, unsigned char* ch)
{
	unsigned char temp;
	if(row==1)
	{
		//10000000
		temp = 0x80 | pos;
	}

	else if(row==2)
	{
		//11000000
		temp = 0xC0 | pos;
	}
	lcd_cmd(temp);

	while(*ch)
	{
		//Display the string
		lcd_data(*ch++);
	}
}















































































/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
