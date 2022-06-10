/// @file      task/keyTask.cpp
/// @author    Hiroshi Mikuriya
/// @copyright Copyright© 2021 Hiroshi Mikuriya
///
/// DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.

#include "main.h"
#include "message/msgdef.h"

namespace
{
constexpr int KEY_COUNT = 4;
/// @brief キーを読み込む
/// @param [out] keys 読み込んだキーの書き込み先
void readKeys(bool (&keys)[KEY_COUNT])
{
  keys[0] = LL_GPIO_IsInputPinSet(BTN1_GPIO_Port, BTN1_Pin) != 0; //
  keys[1] = LL_GPIO_IsInputPinSet(BTN2_GPIO_Port, BTN2_Pin) != 0; //
  keys[2] = LL_GPIO_IsInputPinSet(BTN3_GPIO_Port, BTN3_Pin) != 0; //
  keys[3] = LL_GPIO_IsInputPinSet(BTN4_GPIO_Port, BTN4_Pin) != 0; //
};
} // namespace

extern "C"
{
  /// @brief KEYタスク<br>
  /// キー入力を監視し、変化があればメッセージを送信する
  /// @param [in] argument 未使用
  void keyTaskProc(void const *argument)
  {
    UNUSED(argument);
    const osThreadId handles[KEY_COUNT] = {app1TaskHandle, app2TaskHandle, app3TaskHandle, app4TaskHandle};
    bool pre[KEY_COUNT] = {};
    readKeys(pre);
    for (;;)
    {
      bool cur[KEY_COUNT] = {};
      readKeys(cur);
      for (int i = 0; i < KEY_COUNT; ++i)
      {
        if (pre[i] && !cur[i])
        {
          msg::send(handles[i], msg::KEY_PUSHED);
        }
        pre[i] = cur[i];
      }
      osDelay(50);
    }
  }
} // extern "C"