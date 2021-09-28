//
// Created by guozhenxiong on 2021-09-21.
//

#include "engine.h"
#include "animator/platform/win32/vsync_waiter_win32.h"
namespace wtf {

// | static |
std::unique_ptr<Engine> Engine::Create(Delegate& delegate)
{
    auto thread_host = std::make_unique<ThreadHost>("wtf",
                                                ThreadHost::Type::UI |
                                                ThreadHost::Type::RASTER |
                                                ThreadHost::Type::IO);

    auto task_runners = std::make_unique<TaskRunners>("wtf",
                                                      nullptr,
                                                      thread_host->raster_thread()->GetTaskRunner(),
                                                      thread_host->ui_thread()->GetTaskRunner(),
                                                      thread_host->io_thread()->GetTaskRunner());
    std::unique_ptr<Engine> engine;
    engine.reset(new Engine(delegate, std::move(thread_host), std::move(task_runners)));

    return std::move(engine);
}

Engine::Engine(Delegate& delegate,
               std::unique_ptr<ThreadHost> thread_host,
               std::unique_ptr<TaskRunners> task_runners)
  : delegate_(delegate),
    thread_host_(std::move(thread_host)),
    task_runners_(std::move(task_runners))
{
    auto waiter = std::make_unique<VsyncWaiterWin32>(task_runners_.get());
    animator_ = std::make_unique<Animator>(*this, task_runners_.get(), std::move(waiter));
}

/// | Animator::Delegate |
void Engine::OnAnimatorBeginFrame(fml::TimePoint frame_target_time)
{
    BeginFrame(frame_target_time);
}

void Engine::BeginFrame(fml::TimePoint frame_target_time)
{
    delegate_.OnEngineBeginFrame(frame_target_time);
}

void Engine::ScheduleFrame()
{
    animator_->RequestFrame();
}

} // namespace wtf