//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_DIAGNOSTICS_PROPERTY_H
#define SHOWMAKER_DIAGNOSTICS_PROPERTY_H

#include "wtf/diagnostics/diagnostics_node.h"

namespace sm {
template<class T>
class DiagnosticsProperty : public DiagnosticsNode {
public:
    DiagnosticsProperty(const std::string& name,
                        T value,
                        const std::string& line_prefix,
                        DiagnosticLevel level = DiagnosticLevel::INFO,
                        const DiagnosticsTreeStyle& style = DiagnosticsTreeStyle::SINGLE_LINE,
                        bool show_name = true,
                        bool show_separator = true)
            : value_(value), default_level_(level), DiagnosticsNode(name, line_prefix, style, show_name, show_separator)
    {
    }

private:
    T value_;

    DiagnosticLevel default_level_;
};


} // namespace sm

#endif //SHOWMAKER_DIAGNOSTICS_PROPERTY_H
