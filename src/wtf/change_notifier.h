//
// Created by guozhenxiong on 2021-11-05.
//

#ifndef SHOWMAKER_CHANGE_NOTIFIER_H
#define SHOWMAKER_CHANGE_NOTIFIER_H
#include <list>

#include "listenable.h"

namespace sm {
class ChangeNotifier : public Listenable {
public:
    void AddListener(const std::function<void ()>& listener) override;

private:
    bool DebugAssertNotDisposed();

    bool debug_disposed_ = false;

    int count_ = 0;

    std::vector<std::function<void ()>> listeners_;
};
} // namespace sm

#endif //SHOWMAKER_CHANGE_NOTIFIER_H
