//
// Created by guozhenxiong on 2021-09-18.
//

#include "animator.h"

namespace wtf {
void Animator::AwaitVsync()
{
    waiter_->AsyncWaitForVsync(
            [thiz = this](const fml::TimePoint& frame_target_time) {
                if (thiz) {
                    thiz->BeginFrame(frame_target_time);
                }
            });
}

void Animator::BeginFrame(const fml::TimePoint& frame_target_time)
{
    delegate_->OnAnimatorBeginFrame(frame_target_time);
}

} // namespace wtf