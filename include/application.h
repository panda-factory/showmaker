//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef XXX_APPLICATION_H
#define XXX_APPLICATION_H

namespace wtf {
class Application {
public:
    static Application *Create(int argc, char **argv, void *platformData);

    virtual ~Application()
    {}
};
} // namespace wtf

#endif //XXX_APPLICATION_H
