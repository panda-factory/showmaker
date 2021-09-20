//
// Created by guozhenxiong on 2021-09-20.
//

#include "vsync_waiter_win32.h"

#include <chrono>

void VsyncWaiterWin32::AwaitVSync()
{
    constexpr long long kFPS = (1.0 / 60.0) * 1000 * 1000; //
    const std::chrono::nanoseconds kSingleFrameInterval(kFPS);


}