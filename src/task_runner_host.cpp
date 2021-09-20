//
// Created by guozhenxiong on 2021-09-18.
//

#include "task_runner_host.h"

namespace wtf {

// | static |
std::unique_ptr<TaskRunnerHost> TaskRunnerHost::Create(std::string name_prefix, uint64_t type_mask)
{
    std::unique_ptr<TaskRunnerHost> host;
    host.reset(new TaskRunnerHost());

    if (type_mask & TaskRunnerHost::Type::Platform) {
        host->platform_runner_ = wtf::TaskRunner::Create(name_prefix + ".platform");
    }

    if (type_mask & TaskRunnerHost::Type::UI) {
        host->ui_runner_ = wtf::TaskRunner::Create(name_prefix + ".ui");
    }

    if (type_mask & TaskRunnerHost::Type::RASTER) {
        host->raster_runner_ = wtf::TaskRunner::Create(name_prefix + ".raster");
    }

    if (type_mask & TaskRunnerHost::Type::IO) {
        host->io_runner_ = wtf::TaskRunner::Create(name_prefix + ".io");
    }

    return std::move(host);
}

TaskRunnerHost::TaskRunnerHost() :
    platform_runner_(nullptr),
    ui_runner_(nullptr),
    raster_runner_(nullptr),
    io_runner_(nullptr)
{}

TaskRunnerHost::~TaskRunnerHost()
{}

}