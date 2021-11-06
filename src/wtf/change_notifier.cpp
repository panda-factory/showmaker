//
// Created by guozhenxiong on 2021-11-05.
//

#include "change_notifier.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {
void ChangeNotifier::AddListener(const std::function<void ()>& listener)
{
    FML_CHECK(DebugAssertNotDisposed());
    listeners_.emplace_back() = std::move(listener);
}

bool ChangeNotifier::DebugAssertNotDisposed()
{
    if (debug_disposed_) {
        FML_CHECK(false) << "ChangeNotifier::DebugAssertNotDisposed()";
    }
    return true;
}
} // namespace sm