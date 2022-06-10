/// @file      task/usbTask.cpp
/// @author    Hiroshi Mikuriya
/// @copyright Copyright© 2021 Hiroshi Mikuriya
///
/// DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.

#include "main.h"
#include "message/msgdef.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

namespace
{
constexpr int32_t SIG_TX_END = 1;
}

extern "C"
{
  /// @brief USBタスク<br>
  /// 受信したメッセージをUSB送信する
  /// @param [in] argument 未使用
  void usbTaskProc(void const *argument)
  {
    UNUSED(argument);
    MX_USB_DEVICE_Init();
    msg::registerThread(4);
    for (;;)
    {
      auto res = msg::recv();
      auto msg = res.msg();
      if (msg == 0)
      {
        continue;
      }
      if (msg->type != msg::USB_TX_REQ)
      {
        continue;
      }
      if (CDC_Transmit_FS(const_cast<uint8_t *>(msg->bytes), msg->size) != USBD_OK)
      {
        // TODO error
        return;
      }
      osSignalWait(SIG_TX_END, 10);
    }
  }
  /// @brief USB受信割り込み
  /// @param [in] bytes 受信データの先頭ポインタ
  /// @param [in] size 受信データサイズ
  void usbRxIRQ(uint8_t const *bytes, uint32_t size) { msg::send(usbTaskHandle, msg::USB_TX_REQ, bytes, size); }
  /// @brief USB送信完了割り込み
  /// @param [in] bytes 受信データの先頭ポインタ
  /// @param [in] size 受信データサイズ
  void usbTxEndIRQ(uint8_t const *bytes, uint32_t size)
  {
    UNUSED(bytes);
    UNUSED(size);
    osSignalSet(usbTaskHandle, SIG_TX_END);
  }
} // extern "C"