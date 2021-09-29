//
// Created by guozhenxiong on 2021-09-21.
//

#ifndef STRUGGLE_ENGINE_H
#define STRUGGLE_ENGINE_H

#include "thread_host.h"
#include "task_runners.h"
#include "animator/animator.h"

namespace strg {
class Engine : public Animator::Delegate {
public:
    class Delegate {
    public:
        virtual void OnEngineBeginFrame(fml::TimePoint frame_target_time) = 0;
    };

    static std::unique_ptr<Engine> Create(Delegate& delegate);

    /// | Animator::Delegate |
    void OnAnimatorBeginFrame(fml::TimePoint frame_target_time) override;

    void BeginFrame(fml::TimePoint frame_target_time);

    void ScheduleFrame();

private:
    Engine(Delegate& delegate,
           std::unique_ptr<ThreadHost> thread_host,
           std::unique_ptr<TaskRunners> task_runners);

    Delegate& delegate_;
    std::unique_ptr<ThreadHost> thread_host_;
    std::unique_ptr<TaskRunners> task_runners_;
    std::unique_ptr<Animator> animator_;
};
} // namespace strg

#endif //STRUGGLE_ENGINE_H
