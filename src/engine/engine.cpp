//
// Created by guozhenxiong on 2021-09-21.
//

#include "engine.h"
namespace wtf {

// | static |
std::unique_ptr<Engine> Engine::Create()
{
    std::unique_ptr<Engine> engine;
    engine.reset(new Engine());

    return std::move(engine);
}

Engine::Engine()
{
    thread_host_ = std::make_unique<ThreadHost>("wtf",
                                                ThreadHost::Type::UI |
                                                ThreadHost::Type::RASTER |
                                                ThreadHost::Type::IO);

    task_runners_ = std::make_unique<TaskRunners>("wtf",
                                                  thread_host_->platform_thread()->GetTaskRunner(),
                                                  thread_host_->raster_thread()->GetTaskRunner(),
                                                  thread_host_->ui_thread()->GetTaskRunner(),
                                                  thread_host_->io_thread()->GetTaskRunner());
}

} // namespace wtf
