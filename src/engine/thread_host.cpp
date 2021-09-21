//
// Created by guozhenxiong on 2021-09-18.
//

#include "thread_host.h"

#include "flutter/fml/thread.h"

namespace wtf {

ThreadHost::ThreadHost() = default;

ThreadHost::ThreadHost(ThreadHost&&) = default;

ThreadHost::~ThreadHost() = default;

ThreadHost::ThreadHost(std::string name_prefix_arg, uint64_t mask)
        : name_prefix(name_prefix_arg) {
    if (mask & ThreadHost::Type::Platform) {
        platform_thread_ = std::make_unique<fml::Thread>(name_prefix + ".platform");
    }

    if (mask & ThreadHost::Type::UI) {
        ui_thread_ = std::make_unique<fml::Thread>(name_prefix + ".ui");
    }

    if (mask & ThreadHost::Type::RASTER) {
        raster_thread_ = std::make_unique<fml::Thread>(name_prefix + ".raster");
    }

    if (mask & ThreadHost::Type::IO) {
        io_thread_ = std::make_unique<fml::Thread>(name_prefix + ".io");
    }

    if (mask & ThreadHost::Type::Profiler) {
        profiler_thread_ = std::make_unique<fml::Thread>(name_prefix + ".profiler");
    }
}
}