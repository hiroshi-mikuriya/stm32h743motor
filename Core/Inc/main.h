/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_crs.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_exti.h"
#include "stm32h7xx_ll_cortex.h"
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_tim.h"
#include "stm32h7xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWM_TIM TIM4
#define MOTOR4_ENC_TIM TIM1
#define MOTOR3_ENC_TIM TIM5
#define MOTOR2_ENC_TIM TIM3
#define MOTOR1_ENC_TIM TIM8
#define LED1_RED_Pin LL_GPIO_PIN_2
#define LED1_RED_GPIO_Port GPIOE
#define LED1_GREEN_Pin LL_GPIO_PIN_3
#define LED1_GREEN_GPIO_Port GPIOE
#define LED1_BLUE_Pin LL_GPIO_PIN_4
#define LED1_BLUE_GPIO_Port GPIOE
#define LED2_RED_Pin LL_GPIO_PIN_8
#define LED2_RED_GPIO_Port GPIOI
#define LED2_GREEN_Pin LL_GPIO_PIN_13
#define LED2_GREEN_GPIO_Port GPIOC
#define LED2_BLUE_Pin LL_GPIO_PIN_14
#define LED2_BLUE_GPIO_Port GPIOC
#define LED3_RED_Pin LL_GPIO_PIN_15
#define LED3_RED_GPIO_Port GPIOC
#define LED3_BLUE_Pin LL_GPIO_PIN_9
#define LED3_BLUE_GPIO_Port GPIOI
#define LED3_GREEN_Pin LL_GPIO_PIN_10
#define LED3_GREEN_GPIO_Port GPIOI
#define LED4_RED_Pin LL_GPIO_PIN_11
#define LED4_RED_GPIO_Port GPIOI
#define LED4_GREEN_Pin LL_GPIO_PIN_0
#define LED4_GREEN_GPIO_Port GPIOF
#define LED4_BLUE_Pin LL_GPIO_PIN_1
#define LED4_BLUE_GPIO_Port GPIOF
#define MOTOR3_ENC_A_Pin LL_GPIO_PIN_0
#define MOTOR3_ENC_A_GPIO_Port GPIOA
#define MOTOR3_ENC_B_Pin LL_GPIO_PIN_1
#define MOTOR3_ENC_B_GPIO_Port GPIOA
#define MOTOR4_ENC_A_Pin LL_GPIO_PIN_9
#define MOTOR4_ENC_A_GPIO_Port GPIOE
#define MOTOR4_ENC_B_Pin LL_GPIO_PIN_11
#define MOTOR4_ENC_B_GPIO_Port GPIOE
#define BTN1_Pin LL_GPIO_PIN_8
#define BTN1_GPIO_Port GPIOH
#define BTN2_Pin LL_GPIO_PIN_9
#define BTN2_GPIO_Port GPIOH
#define BTN3_Pin LL_GPIO_PIN_10
#define BTN3_GPIO_Port GPIOH
#define BTN4_Pin LL_GPIO_PIN_11
#define BTN4_GPIO_Port GPIOH
#define MOTOR4_CTRL1_Pin LL_GPIO_PIN_14
#define MOTOR4_CTRL1_GPIO_Port GPIOA
#define MOTOR4_CTRL2_Pin LL_GPIO_PIN_10
#define MOTOR4_CTRL2_GPIO_Port GPIOC
#define MOTOR3_CTRL1_Pin LL_GPIO_PIN_12
#define MOTOR3_CTRL1_GPIO_Port GPIOC
#define MOTOR3_CTRL2_Pin LL_GPIO_PIN_1
#define MOTOR3_CTRL2_GPIO_Port GPIOD
#define MOTOR2_CTRL1_Pin LL_GPIO_PIN_3
#define MOTOR2_CTRL1_GPIO_Port GPIOD
#define MOTOR2_CTRL2_Pin LL_GPIO_PIN_5
#define MOTOR2_CTRL2_GPIO_Port GPIOD
#define MOTOR1_CTRL1_Pin LL_GPIO_PIN_7
#define MOTOR1_CTRL1_GPIO_Port GPIOD
#define MOTOR1_CTRL2_Pin LL_GPIO_PIN_10
#define MOTOR1_CTRL2_GPIO_Port GPIOG
#define MOTOR2_ENC_A_Pin LL_GPIO_PIN_4
#define MOTOR2_ENC_A_GPIO_Port GPIOB
#define MOTOR2_ENC_B_Pin LL_GPIO_PIN_5
#define MOTOR2_ENC_B_GPIO_Port GPIOB
#define MOTOR1_PWM_Pin LL_GPIO_PIN_6
#define MOTOR1_PWM_GPIO_Port GPIOB
#define MOTOR2_PWM_Pin LL_GPIO_PIN_7
#define MOTOR2_PWM_GPIO_Port GPIOB
#define MOTOR3_PWM_Pin LL_GPIO_PIN_8
#define MOTOR3_PWM_GPIO_Port GPIOB
#define MOTOR4_PWM_Pin LL_GPIO_PIN_9
#define MOTOR4_PWM_GPIO_Port GPIOB
#define MOTOR1_ENC_A_Pin LL_GPIO_PIN_5
#define MOTOR1_ENC_A_GPIO_Port GPIOI
#define MOTOR1_ENC_B_Pin LL_GPIO_PIN_6
#define MOTOR1_ENC_B_GPIO_Port GPIOI
/* USER CODE BEGIN Private defines */
extern osThreadId usbTaskHandle;
extern osThreadId keyTaskHandle;
extern osThreadId adcTaskHandle;
extern osThreadId app1TaskHandle;
extern osThreadId app2TaskHandle;
extern osThreadId app3TaskHandle;
extern osThreadId app4TaskHandle;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
