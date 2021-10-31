//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_DIAGNOSTIC_PROPERTIES_BUILDER_H
#define SHOWMAKER_DIAGNOSTIC_PROPERTIES_BUILDER_H

#include <list>

#include "wtf/diagnostics/diagnostics_node.h"

namespace sm {
class DiagnosticPropertiesBuilder {
public:
    void Add(const DiagnosticsNode& property);

    inline std::list<DiagnosticsNode>& properties() { return properties_; }
private:
    std::list<DiagnosticsNode> properties_;
};
} // namespace sm

#endif //SHOWMAKER_DIAGNOSTIC_PROPERTIES_BUILDER_H
