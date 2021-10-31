//
// Created by guozhenxiong on 2021-10-31.
//

#ifndef SHOWMAKER_TEXT_TREE_RENDERER_H
#define SHOWMAKER_TEXT_TREE_RENDERER_H
#include <string>

#include "wtf/diagnostics/diagnostics_node.h"
#include "wtf/diagnostics/text_tree_configuration.h"

namespace sm {
class TextTreeRenderer {
public:
    std::string Render(DiagnosticsNode node,
                       std::string prefixLineOne,
                       std::string prefixOtherLines,
                       TextTreeConfiguration parentConfiguration);

    TextTreeRenderer(DiagnosticLevel minLevel = DiagnosticLevel::DEBUG,
                     int wrap_width = 100,
                     int wrap_width_properties = 65,
                     int max_descendents_truncatable_node = -1);
private:
    TextTreeConfiguration ChildTextConfiguration(DiagnosticsNode child,
                                                 TextTreeConfiguration textStyle);

    std::string DebugRender(DiagnosticsNode node,
                            std::string prefixLineOne = "",
                            std::string prefixOtherLines = "",
                            TextTreeConfiguration parentConfiguration = {});
    int wrap_width_;
    int wrap_width_properties_;
    DiagnosticLevel min_level_;
    int max_descendents_truncatable_node_;
};
} // namespace sm

#endif //SHOWMAKER_TEXT_TREE_RENDERER_H
