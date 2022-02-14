/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void PerdeuJogo()
{
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
	HAL_Delay(1000);
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
	HAL_Delay(200);
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
}

void GanhouJogo()
{
	for(int h = 0; h< 3; h++)
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
		HAL_Delay(200);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
		HAL_Delay(200);
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int queue[10] = {5};
	int queueReply[10]= {5};
	int queueAux = 0;
	int pinTurnOff = 0;
	int startGame = 0;
	int delay;
	int pressButton;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //Irá conferir se o botão de start foi iniciado, e iniciará o jogo
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
	  {
		  startGame = 1;
	  }

	  //Apenas uma correção, pois quando era iniciado o jogo, os leds iniciavam ligados.
	  //Aqui é setado o tempo inicial de delay, e nosso pressButton, que seu estado indica se está na zona
	  //onde os led ficam acessos, ou na que o botão é precionado.
	  if(pinTurnOff == 0)
	  {
		  delay = 500;
		  pressButton = 1;
		  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
		  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
		  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
		  pinTurnOff = 1;
	  }

	  //Zona onde o led irá piscar
	  if(startGame == 1)
	  {
		  //zera nosso cursor da fila
			int i = 0;

			//confere se ganhou o jogo
			if(queueAux == 10)
			{
				GanhouJogo();
				return;
			}

			//Escolhe um led aleatório para acender, usando para isso um tick do clock, e adiciona na fila
			srand(HAL_GetTick());
			queue[queueAux] = rand() % 4;

		//Laço responsavel por piscar os leds
		  while(pressButton == 1)
		  {
			  HAL_Delay(1000);

			  switch(queue[i])
			  {
			  	  case 0:
			  		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			  		HAL_Delay(delay);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
					break;
			  	  case 1:
			  		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
			  		HAL_Delay(delay);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
					break;
			  	  case 2:
			  		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
			  		HAL_Delay(delay);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
					break;
			  	  case 3:
			  		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
			  		HAL_Delay(delay);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
					break;
			  	  default:
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			  		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
					HAL_Delay(delay);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
					break;
			  }
			  // se o nosso cursor chegar no valor atual da fila, ele aumenta nosso auxiliar e sai do laço
			  if(i == queueAux)
			  {
				pressButton = 0;
				queueAux++;
			  }
			  i++;

		  }

		  //Aqui nosso cursor é zerado
		  i = 0;

		  //Laço responsável por esperar a resposta dos botões
		  while(pressButton == 0)
		  {
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
			  {
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
				  HAL_Delay(delay);
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);

				  //Aqui armazena a resposta
				  queueReply[i] = 0;
				  //Aqui confere se a resposta nessa posição é igual
				  if(queue[i] == queueReply[i]){
					  // confere se ja chegou ao final
					  // queueAux-1 pois nos aumentamos o tamanho dele no outro laço
					  if(i == (queueAux-1)){
						  pressButton = 1;
						  delay -= 35;
					  }
					  i++;
				  }
				  // aqui a gente perdeu o jogo, caso seja diferente que a queue
				  else{
					  pressButton = 1;
					  PerdeuJogo();
					  return;
				  }
			  }
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
			  {
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
				  HAL_Delay(delay);
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
				  queueReply[i] = 1;
				  if(queue[i] == queueReply[i]){
					  if(i == (queueAux-1)){
						  pressButton = 1;
						  delay -= 35;
					  }
					  i++;
				  }
				  else{
					  pressButton = 1;
					  PerdeuJogo();
					  return;
				  }
			  }
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6))
			  {
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
				  HAL_Delay(delay);
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2);
				  queueReply[i] = 2;
				  if(queue[i] == queueReply[i]){
					  if(i == (queueAux-1)){
						  pressButton = 1;
						  delay -= 35;
					  }
					  i++;
				  }
				  else{
					  pressButton = 1;
					  PerdeuJogo();
					  return;
				  }
			  }
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
			  {
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
				  HAL_Delay(delay);
				  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
				  queueReply[i] = 3;
				  if(queue[i] == queueReply[i]){
					  if(i == (queueAux-1)){
						  pressButton = 1;
						  delay -= 35;
					  }
					  i++;
				  }
				  else{
					  pressButton = 1;
					  PerdeuJogo();
					  return;
				  }
			  }

		  }
	  }

  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

