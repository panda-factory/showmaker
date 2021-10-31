//
// Created by guozhenxiong on 2021-10-30.
//

#include "diagnostic_properties_builder.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {
void DiagnosticPropertiesBuilder::Add(const DiagnosticsNode& property) {
    properties_.emplace_back(std::move(property));
}
} // namespace sm