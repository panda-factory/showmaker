//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef STRUGGLE_APPLICATION_H
#define STRUGGLE_APPLICATION_H

namespace strg {
class Application {
public:
    static Application *Create(int argc, char **argv, void *platformData);

    virtual ~Application()
    {}
};
} // namespace strg

#endif //STRUGGLE_APPLICATION_H
