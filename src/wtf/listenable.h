//
// Created by guozhenxiong on 2021-11-05.
//

#ifndef SHOWMAKER_LISTENABLE_H
#define SHOWMAKER_LISTENABLE_H
#include <functional>

namespace sm {
class Listenable {
public:
    /// Register a closure to be called when the object notifies its listeners.
    virtual void AddListener(const std::function<void ()>& listener) = 0;
};
} // namespace sm
#endif //SHOWMAKER_LISTENABLE_H
