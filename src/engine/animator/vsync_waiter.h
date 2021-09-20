//
// Created by guozhenxiong on 2021-09-20.
//

#ifndef XXX_VSYNC_WAITER_H
#define XXX_VSYNC_WAITER_H

#include <functional>

class VsyncWaiter {
public:
    void AsyncWaitForVsync();

    virtual void AwaitVSync() = 0;

    void Invoke();

private:
    std::function<void ()> invoker_;
};


#endif //XXX_VSYNC_WAITER_H
