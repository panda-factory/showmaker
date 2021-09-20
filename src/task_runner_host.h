//
// Created by guozhenxiong on 2021-09-18.
//

#ifndef XXX_TASK_RUNNER_HOST_H
#define XXX_TASK_RUNNER_HOST_H

#include <memory>
#include <string>

#include <taskrunner/include/task_runner/task_runner.h>

namespace wtf {
class TaskRunnerHost {
public:
    enum Type {
        Platform = 1 << 0,
        UI = 1 << 1,
        RASTER = 1 << 2,
        IO = 1 << 3,
    };

    static std::unique_ptr<TaskRunnerHost> Create(std::string name_prefix, uint64_t type_mask);

    inline wtf::TaskRunner* platform_runner() { return platform_runner_.get(); }

    inline wtf::TaskRunner* ui_runner() { return ui_runner_.get(); }

    inline wtf::TaskRunner* raster_runner() { return raster_runner_.get(); }

    inline wtf::TaskRunner* io_runner() { return io_runner_.get(); }

    ~TaskRunnerHost();

private:
    TaskRunnerHost();

    // | field |
    std::string name_prefix;
    std::unique_ptr<wtf::TaskRunner> platform_runner_;
    std::unique_ptr<wtf::TaskRunner> ui_runner_;
    std::unique_ptr<wtf::TaskRunner> raster_runner_;
    std::unique_ptr<wtf::TaskRunner> io_runner_;
};
} // namespace wtf

#endif //XXX_TASK_RUNNER_HOST_H
