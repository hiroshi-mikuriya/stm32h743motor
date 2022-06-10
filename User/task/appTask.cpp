/// @file      task/appTask.cpp
/// @author    Hiroshi Mikuriya
/// @copyright Copyright© 2021 Hiroshi Mikuriya
///
/// DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.

#include "main.h"
#include "message/msgdef.h"
#include <algorithm>
#include <cmath>

namespace
{
/// @brief GPIO制御クラス
struct GpioType
{
  uint32_t pin;       ///< ピン番号
  GPIO_TypeDef *gpio; ///< GPIO

  /// @brief 信号レベルをHIGHにする
  void high() const { LL_GPIO_SetOutputPin(gpio, pin); }
  /// @brief 信号レベルをLOWにする
  void low() const { LL_GPIO_ResetOutputPin(gpio, pin); }
  /// @brief 信号レベルをトグルする
  void toggle() const { LL_GPIO_TogglePin(gpio, pin); }
};
/// @brief APPタスク内部処理
/// @param [in] red 赤LED
/// @param [in] green 緑LED
/// @param [in] blue 青LED
/// @param [in] motor1 モータ制御１
/// @param [in] motor2 モータ制御２
/// @param [in] SetCompareValue PWM値を設定する関数
/// @param [in] encTIM エンコーダ値を読み出すペリフェラル
void appTaskImpl(                                     //
    GpioType const &red,                              //
    GpioType const &green,                            //
    GpioType const &blue,                             //
    GpioType const &motor1,                           //
    GpioType const &motor2,                           //
    void (*SetCompareValue)(TIM_TypeDef *, uint32_t), //
    TIM_TypeDef *encTIM                               //
)
{
  msg::registerThread(4);
  LL_TIM_SetCounter(encTIM, 0);
  LL_TIM_EnableCounter(encTIM);
  int32_t preCounter = 0;
  int32_t encCounter = 0;
  bool running = false;
  bool reverse = false;
  for (;;)
  {
    auto res = msg::recv();
    auto msg = res.msg();
    if (msg == 0)
    {
      continue;
    }
    switch (msg->type)
    {
    case msg::KEY_PUSHED:
      running = !running;
      break;
    case msg::ADC_VALUE:
    {
      int adc = *reinterpret_cast<uint16_t const *>(msg->bytes);
      constexpr int CENTER_ANALOG = 2048;
      constexpr uint16_t MAX_PWM = 2047;
      reverse = adc < CENTER_ANALOG;
      uint16_t pwm = std::min(static_cast<uint16_t>(std::abs(adc - CENTER_ANALOG)), MAX_PWM);
      SetCompareValue(PWM_TIM, running ? pwm : 0);
      // メッセージの内容と処理が不一致だが、定期的に行われる処理なのでここでエンコーダ値を更新する。オーバーフローするかも。
      int32_t cnt = static_cast<int32_t>(LL_TIM_GetCounter(encTIM));
      encCounter += cnt - preCounter;
      preCounter = cnt;
      break;
    }
    }
    if (running)
    {
      green.high();
      red.low();
      if (reverse)
      {
        motor1.low();
        motor2.high();
      }
      else
      {
        motor1.high();
        motor2.low();
      }
    }
    else
    {
      green.low();
      red.high();
      motor1.high();
      motor2.high();
    }
  }
}
} // namespace

extern "C"
{
  /// @brief APP1タスク<br>
  /// モータ1に関する制御を行う
  /// @param [in] argument 未使用
  void app1TaskProc(void const *argument)
  {
    UNUSED(argument);
    // PWMチャネルの初期化をスレッドで分散すると、LL_TIM_EnableCounter,
    // LL_TIM_EnableAllOutputsを呼び出す前に同期が必要になってしまうため、全チャネルの初期化をここで行う。
    LL_TIM_CC_EnableChannel(PWM_TIM, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(PWM_TIM, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(PWM_TIM, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(PWM_TIM, LL_TIM_CHANNEL_CH4);
    LL_TIM_EnableCounter(PWM_TIM);
    LL_TIM_EnableAllOutputs(PWM_TIM);

    appTaskImpl({LED1_RED_Pin, LED1_RED_GPIO_Port},         //
                {LED1_GREEN_Pin, LED1_GREEN_GPIO_Port},     //
                {LED1_BLUE_Pin, LED1_BLUE_GPIO_Port},       //
                {MOTOR1_CTRL1_Pin, MOTOR1_CTRL1_GPIO_Port}, //
                {MOTOR1_CTRL2_Pin, MOTOR1_CTRL2_GPIO_Port}, //
                LL_TIM_OC_SetCompareCH1,                    //
                MOTOR1_ENC_TIM                              //
    );
  }
  /// @brief APP2タスク<br>
  /// モータ2に関する制御を行う
  /// @param [in] argument 未使用
  void app2TaskProc(void const *argument)
  {
    UNUSED(argument);
    appTaskImpl({LED2_RED_Pin, LED2_RED_GPIO_Port},         //
                {LED2_GREEN_Pin, LED2_GREEN_GPIO_Port},     //
                {LED2_BLUE_Pin, LED2_BLUE_GPIO_Port},       //
                {MOTOR2_CTRL1_Pin, MOTOR2_CTRL1_GPIO_Port}, //
                {MOTOR2_CTRL2_Pin, MOTOR2_CTRL2_GPIO_Port}, //
                LL_TIM_OC_SetCompareCH2,                    //
                MOTOR2_ENC_TIM                              //
    );
  }
  /// @brief APP3タスク<br>
  /// モータ3に関する制御を行う
  /// @param [in] argument 未使用
  void app3TaskProc(void const *argument)
  {
    UNUSED(argument);
    appTaskImpl({LED3_RED_Pin, LED3_RED_GPIO_Port},         //
                {LED3_GREEN_Pin, LED3_GREEN_GPIO_Port},     //
                {LED3_BLUE_Pin, LED3_BLUE_GPIO_Port},       //
                {MOTOR3_CTRL1_Pin, MOTOR3_CTRL1_GPIO_Port}, //
                {MOTOR3_CTRL2_Pin, MOTOR3_CTRL2_GPIO_Port}, //
                LL_TIM_OC_SetCompareCH3,                    //
                MOTOR3_ENC_TIM                              //
    );
  }
  /// @brief APP4タスク<br>
  /// モータ4に関する制御を行う
  /// @param [in] argument 未使用
  void app4TaskProc(void const *argument)
  {
    UNUSED(argument);
    appTaskImpl({LED4_RED_Pin, LED4_RED_GPIO_Port},         //
                {LED4_GREEN_Pin, LED4_GREEN_GPIO_Port},     //
                {LED4_BLUE_Pin, LED4_BLUE_GPIO_Port},       //
                {MOTOR4_CTRL1_Pin, MOTOR4_CTRL1_GPIO_Port}, //
                {MOTOR4_CTRL2_Pin, MOTOR4_CTRL2_GPIO_Port}, //
                LL_TIM_OC_SetCompareCH4,                    //
                MOTOR4_ENC_TIM                              //
    );
  }
} // extern "C"