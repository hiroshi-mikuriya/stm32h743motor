/// @file      message/msgdef.h
/// @author    Hiroshi Mikuriya
/// @copyright Copyright© 2021 Hiroshi Mikuriya
///
/// DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.

#pragma once

#include "msglib.h"

namespace msg
{
constexpr ID KEY_PUSHED = 1; ///< キー押下通知
constexpr ID ADC_VALUE = 2;  ///< ADCの値を通知する
constexpr ID USB_TX_REQ = 3; ///< USB送信依頼
} // namespace msg
