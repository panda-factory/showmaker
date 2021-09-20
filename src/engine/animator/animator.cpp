//
// Created by guozhenxiong on 2021-09-18.
//

#include "animator.h"

namespace wtf {
void Animator::AwaitVsync()
{
    waiter_->AsyncWaitForVsync();
}

void Animator::BeginFrame()
{}

} // namespace wtf