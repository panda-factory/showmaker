//
// Created by guozhenxiong on 2021-09-18.
//

#ifndef STRUGGLE_THREAD_HOST_H
#define STRUGGLE_THREAD_HOST_H

#include <memory>
#include <string>

#include "flutter/fml/thread.h"

namespace strg {

class ThreadHost {
public:
    enum Type {
        Platform = 1 << 0,
        UI = 1 << 1,
        RASTER = 1 << 2,
        IO = 1 << 3,
        Profiler = 1 << 4,
    };

    inline const fml::Thread* platform_thread() { return platform_thread_.get(); }
    inline const fml::Thread* ui_thread() { return ui_thread_.get(); }
    inline const fml::Thread* raster_thread() { return raster_thread_.get(); }
    inline const fml::Thread* io_thread() { return io_thread_.get(); }

    ThreadHost();

    ThreadHost(ThreadHost&&);

    ThreadHost& operator=(ThreadHost&&) = default;

    ThreadHost(std::string name_prefix, uint64_t type_mask);

    ~ThreadHost();

private:
    std::string name_prefix;
    std::unique_ptr<fml::Thread> platform_thread_;
    std::unique_ptr<fml::Thread> ui_thread_;
    std::unique_ptr<fml::Thread> raster_thread_;
    std::unique_ptr<fml::Thread> io_thread_;
    std::unique_ptr<fml::Thread> profiler_thread_;
};
} // namespace strg

#endif //STRUGGLE_THREAD_HOST_H
