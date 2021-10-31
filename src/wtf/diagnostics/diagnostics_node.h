//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_DIAGNOSTICS_NODE_H
#define SHOWMAKER_DIAGNOSTICS_NODE_H

#include <string>
#include <vector>

#include "wtf/diagnostics/diagnostics_tree_style.h"
#include "wtf/diagnostics/diagnostic_level.h"
#include "wtf/diagnostics/text_tree_configuration.h"

namespace sm {
class DiagnosticsNode {
public:
    virtual inline bool AllowWrap() { return false; }

    virtual inline bool AllowNameWrap() { return false; }

    virtual inline bool AllowTruncate() { return false; }

    virtual std::string EmptyBodyDescription() { return ""; }

    inline bool IsFiltered(DiagnosticLevel min_level) {
#ifndef NDEBUG
        return GetLevel() < min_level;
#else
        return true;
#endif
    }

    inline DiagnosticLevel GetLevel() {
#ifndef NDEBUG
        return DiagnosticLevel::INFO;
#else
        return DiagnosticLevel::HIDDEN;
#endif
    }

    std::vector<DiagnosticsNode*> GetChildren() { return {}; }

    std::vector<DiagnosticsNode*> GetProperties() { return {}; }

    std::string ToDescription(TextTreeConfiguration parentConfiguration) { return ""; }

    std::string ToString(TextTreeConfiguration parentConfiguration = {},
                         DiagnosticLevel minLevel = DiagnosticLevel::INFO);

    std::string ToStringDeep(std::string prefixOtherLines,
                             std::string prefixLineOne = "",
                             TextTreeConfiguration parentConfiguration = {},
                             DiagnosticLevel minLevel = DiagnosticLevel::DEBUG);

    inline const std::string& line_prefix() { return line_prefix_; }

    inline bool show_name() { return show_name_; }

    inline bool show_separator() { return show_separator_; }

    inline const std::string& name() { return name_; }

    inline const DiagnosticsTreeStyle& style() { return style_; }

    DiagnosticsNode(const std::string& name,
                    const std::string& line_prefix,
                    const DiagnosticsTreeStyle& style,
                    bool show_name = true,
                    bool show_separator = true);

    TextTreeConfiguration GetTextTreeConfiguration();
protected:

private:
    bool show_name_;

    bool show_separator_;

    std::string name_;

    const std::string line_prefix_;

    const DiagnosticsTreeStyle style_;
};
} // namespace sm

#endif //SHOWMAKER_DIAGNOSTICS_NODE_H
