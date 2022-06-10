/// @file      task/adcTask.cpp
/// @author    Hiroshi Mikuriya
/// @copyright Copyright© 2021 Hiroshi Mikuriya
///
/// DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.

#include "main.h"
#include "message/msgdef.h"

namespace
{
constexpr int32_t SIG_ADC_HALF = 1 << 0;
constexpr int32_t SIG_ADC_CPLT = 1 << 1;
constexpr int COUNT_OF_ADC = 4;
ALIGN_32BYTES(uint16_t dmaBuffer[COUNT_OF_ADC]);
} // namespace

extern "C"
{
  /// @brief ADCタスク<br>
  /// 可変抵抗の抵抗値を定期的に読み取りメッセージを送信する
  /// @param [in] argument 未使用
  void adcTaskProc(void const *argument)
  {
    UNUSED(argument);
    osDelay(100); // appタスク起動まで待機
    extern ADC_HandleTypeDef hadc1;
    if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
    {
      Error_Handler();
    }
    if (HAL_ADC_Start_DMA(&hadc1, reinterpret_cast<uint32_t *>(dmaBuffer), COUNT_OF_ADC) != HAL_OK)
    {
      Error_Handler();
    }
    for (;;)
    {
      osEvent ev = osSignalWait(SIG_ADC_HALF | SIG_ADC_CPLT, osWaitForever);
      if (ev.value.signals & SIG_ADC_HALF)
      {
        msg::send(app1TaskHandle, msg::ADC_VALUE, dmaBuffer[0]);
        msg::send(app2TaskHandle, msg::ADC_VALUE, dmaBuffer[1]);
      }
      if (ev.value.signals & SIG_ADC_CPLT)
      {
        msg::send(app3TaskHandle, msg::ADC_VALUE, dmaBuffer[2]);
        msg::send(app4TaskHandle, msg::ADC_VALUE, dmaBuffer[3]);
      }
    }
  }
} // extern "C"

/**
 * @brief  Conversion complete callback in non-blocking mode
 * @param  hadc: ADC handle
 * @retval None
 */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
  UNUSED(hadc);
  osSignalSet(adcTaskHandle, SIG_ADC_HALF);
}

/**
 * @brief  Conversion DMA half-transfer callback in non-blocking mode
 * @param  hadc: ADC handle
 * @retval None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  UNUSED(hadc);
  osSignalSet(adcTaskHandle, SIG_ADC_CPLT);
}
