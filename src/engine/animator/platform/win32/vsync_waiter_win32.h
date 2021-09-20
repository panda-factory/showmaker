//
// Created by guozhenxiong on 2021-09-20.
//

#ifndef XXX_VSYNC_WAITER_WIN32_H
#define XXX_VSYNC_WAITER_WIN32_H

#include "vsync_waiter.h"


class VsyncWaiterWin32 : public VsyncWaiter {
public:
    // | VsyncWaiter |
    void AwaitVSync() override;
};


#endif //XXX_VSYNC_WAITER_WIN32_H
