//
// Created by guozhenxiong on 2021-09-21.
//

#ifndef XXX_ENGINE_H
#define XXX_ENGINE_H

#include "thread_host.h"
#include "task_runners.h"

namespace wtf {
class Engine {
public:
    static std::unique_ptr<Engine> Create();

private:
    Engine();

    std::unique_ptr<ThreadHost> thread_host_;
    std::unique_ptr<TaskRunners> task_runners_;
};
} // namespace wtf

#endif //XXX_ENGINE_H
