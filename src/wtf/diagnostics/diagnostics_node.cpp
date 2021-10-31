//
// Created by guozhenxiong on 2021-10-30.
//

#include "diagnostics_node.h"
#include "wtf/diagnostics/text_tree_renderer.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

DiagnosticsNode::DiagnosticsNode(const std::string& name,
                                 const std::string& line_prefix,
                                 const DiagnosticsTreeStyle& style,
                                 bool show_name,
                                 bool show_separator)
  : name_(name), line_prefix_(line_prefix), style_(style), show_name_(show_name), show_separator_(show_separator)
{
    FML_CHECK(!name.empty());
    FML_CHECK(!name.ends_with(":"))
        << "Names of diagnostic nodes must not end with colons." << std::endl
        << "name: " << name;
}

TextTreeConfiguration DiagnosticsNode::GetTextTreeConfiguration()
{
    switch (style_) {
        case DiagnosticsTreeStyle::NONE:
            return {};
        case DiagnosticsTreeStyle::DENSE:
            return TextTreeConfiguration::DENSE_TEXT_CONFIGURATION;
        case DiagnosticsTreeStyle::SPARSE:
            return TextTreeConfiguration::SPARSE_TEXT_CONFIGURATION;
        //case DiagnosticsTreeStyle.offstage:
        //    return dashedTextConfiguration;
        //case DiagnosticsTreeStyle.whitespace:
        //    return whitespaceTextConfiguration;
        //case DiagnosticsTreeStyle.transition:
        //    return transitionTextConfiguration;
        case DiagnosticsTreeStyle::SINGLE_LINE:
            return TextTreeConfiguration::SINGLE_LINE_TEXT_CONFIGURATION;
        //case DiagnosticsTreeStyle.errorProperty:
        //    return errorPropertyTextConfiguration;
        //case DiagnosticsTreeStyle.shallow:
        //    return shallowTextConfiguration;
        //case DiagnosticsTreeStyle.error:
        //    return errorTextConfiguration;
        //case DiagnosticsTreeStyle.truncateChildren:
        //    // Truncate children doesn't really need its own text style as the
        //    // rendering is quite custom.
        //    return whitespaceTextConfiguration;
        //case DiagnosticsTreeStyle.flat:
        //    return flatTextConfiguration;
    }
}

std::string DiagnosticsNode::ToString(TextTreeConfiguration parentConfiguration,
                                      DiagnosticLevel minLevel)
{
    std::string result;
    if (IsSingleLine(style_)) {
        result = ToStringDeep("", "", parentConfiguration, minLevel);
    } else {
        /*final String description = toDescription(parentConfiguration: parentConfiguration)!;

        if (name == null || name!.isEmpty || !showName) {
            result = description;
        } else {
            result = description.contains('\n') ? '$name$_separator\n$description'
                                                : '$name$_separator $description';
        }*/
    }
    return result;
}

std::string DiagnosticsNode::ToStringDeep(std::string prefixOtherLines,
                                          std::string prefixLineOne,
                                          TextTreeConfiguration parentConfiguration,
                                          DiagnosticLevel minLevel)
{

    std::string result = TextTreeRenderer(minLevel, 65).Render(
            *this,
            prefixLineOne,
            prefixOtherLines,
            parentConfiguration);

    return std::move(result);
}
} // namespace sm