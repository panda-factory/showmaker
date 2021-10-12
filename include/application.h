//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef SHOWMAKER_APPLICATION_H
#define SHOWMAKER_APPLICATION_H

namespace sm {
class Application {
public:
    static Application *Create(int argc, char **argv, void *platformData);

    virtual ~Application()
    {}
};
} // namespace sm

#endif //SHOWMAKER_APPLICATION_H
