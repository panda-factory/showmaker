//
// Created by guozhenxiong on 2021-09-18.
//

#include "animator.h"

namespace strg {

Animator::Animator(Delegate& delegate,
                   TaskRunners* task_runners,
                   std::unique_ptr<VsyncWaiter> waiter)
  : delegate_(delegate), task_runners_(std::move(task_runners)), waiter_(std::move(waiter))
{}

void Animator::AwaitVSync()
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
    delegate_.OnAnimatorBeginFrame(frame_target_time);
}

void Animator::RequestFrame()
{
    task_runners_->GetUITaskRunner()->PostTask(
            [thiz = this]() {
                if (!thiz) {
                    return;
                }
                thiz->AwaitVSync();
            });
}

} // namespace strg