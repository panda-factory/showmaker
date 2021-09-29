//
// Created by guozhenxiong on 2021-09-21.
//

#ifndef STRUGGLE_TASK_RUNNERS_H
#define STRUGGLE_TASK_RUNNERS_H

#include <flutter/fml/task_runner.h>

namespace strg {

class TaskRunners {
public:
    TaskRunners(std::string label,
                fml::RefPtr<fml::TaskRunner> platform,
                fml::RefPtr<fml::TaskRunner> raster,
                fml::RefPtr<fml::TaskRunner> ui,
                fml::RefPtr<fml::TaskRunner> io);

    TaskRunners(const TaskRunners& other);

    ~TaskRunners();

    const std::string& GetLabel() const;

    fml::RefPtr<fml::TaskRunner> GetPlatformTaskRunner() const;

    fml::RefPtr<fml::TaskRunner> GetUITaskRunner() const;

    fml::RefPtr<fml::TaskRunner> GetIOTaskRunner() const;

    fml::RefPtr<fml::TaskRunner> GetRasterTaskRunner() const;

    bool IsValid() const;

private:
    const std::string label_;
    fml::RefPtr<fml::TaskRunner> platform_;
    fml::RefPtr<fml::TaskRunner> raster_;
    fml::RefPtr<fml::TaskRunner> ui_;
    fml::RefPtr<fml::TaskRunner> io_;
};
}

#endif //STRUGGLE_TASK_RUNNERS_H
