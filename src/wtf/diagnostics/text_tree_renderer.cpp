//
// Created by guozhenxiong on 2021-10-31.
//

#include "text_tree_renderer.h"
#include <vector>
#include <functional>
#include <sstream>
#include <algorithm>
#include "wtf/diagnostics/prefixed_string_builder.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {


TextTreeRenderer::TextTreeRenderer(DiagnosticLevel minLevel,
                                   int wrap_width,
                                   int wrap_width_properties,
                                   int max_descendents_truncatable_node)
  : min_level_(minLevel),
    wrap_width_(wrap_width),
    wrap_width_properties_(wrap_width_properties),
    max_descendents_truncatable_node_ (max_descendents_truncatable_node)
{}

/// Renders a [node] to a String.
std::string TextTreeRenderer::Render(DiagnosticsNode node,
                                     std::string prefixLineOne,
                                     std::string prefixOtherLines,
                                     TextTreeConfiguration parentConfiguration)
{
#ifndef NDEBUG
    return DebugRender(node,
                       prefixLineOne,
                       prefixOtherLines,
                       parentConfiguration);
#else
return "";
#endif
}


TextTreeConfiguration TextTreeRenderer::ChildTextConfiguration(DiagnosticsNode child,
                                             TextTreeConfiguration textStyle)
{
    DiagnosticsTreeStyle childStyle = child.style();
    return (IsSingleLine(childStyle) || childStyle == DiagnosticsTreeStyle::ERROR_PROPERTY) ? textStyle : child.GetTextTreeConfiguration();
}

std::string TextTreeRenderer::DebugRender(DiagnosticsNode node,
                                          std::string prefixLineOne,
                                          std::string prefixOtherLines,
                                          TextTreeConfiguration parentConfiguration)
{
    const bool is_single_line = IsSingleLine(node.style()) && parentConfiguration.lineBreakProperties != true;
    prefixOtherLines = prefixOtherLines.empty() ? prefixLineOne : prefixOtherLines;
    if (!node.line_prefix().empty()) {
        prefixLineOne += node.line_prefix();
        prefixOtherLines += node.line_prefix();
    }

    const TextTreeConfiguration config = node.GetTextTreeConfiguration();
    if (prefixOtherLines.empty()) {
        prefixOtherLines += config.prefixOtherLinesRootNode;
    }

    if (node.style() == DiagnosticsTreeStyle::TRUNCATE_CHILDREN) {
        // This style is different enough that it isn't worthwhile to reuse the
        // existing logic.
        std::vector<std::string> descendants;
        const int maxDepth = 5;
        int depth = 0;
        const int maxLines = 25;
        int lines = 0;
        std::function<void(DiagnosticsNode node)> visitor = [&] (DiagnosticsNode node) {
            for (const auto& child : node.GetChildren()) {
                if (lines < maxLines) {
                    depth += 1;
                    descendants.emplace_back("$prefixOtherLines${"  " * depth}$child");
                    if (depth < maxDepth)
                        visitor(*child);
                    depth -= 1;
                } else if (lines == maxLines) {
                    descendants.emplace_back("$prefixOtherLines  ...(descendants list truncated after $lines lines)");
                }
                lines += 1;
            }
        };
        visitor(node);
        std::ostringstream information(prefixLineOne);
        if (lines > 1) {
            information << "This ${node.name} had the following descendants (showing up to depth $maxDepth):";
        } else if (descendants.size() == 1) {
            information << "This ${node.name} had the following child:";
        } else {
            information << "This ${node.name} has no descendants.";
        }
        for (const auto& descendant : descendants) {
            information << descendant << std::endl;
        }
        return information.str();
    }

    PrefixedStringBuilder builder = PrefixedStringBuilder(
            prefixLineOne, prefixOtherLines,
            std::max(wrap_width_, static_cast<int>(prefixOtherLines.size() + wrap_width_properties_)));

    std::vector<DiagnosticsNode*> children = node.GetChildren();
    std::string description = node.ToDescription(parentConfiguration);
    if (!config.beforeName.empty()) {
        builder.Write(config.beforeName);
    }
    bool wrapName = !is_single_line && node.AllowNameWrap();
    bool wrapDescription = !is_single_line && node.AllowWrap();
    bool uppercaseTitle = node.style() == DiagnosticsTreeStyle::ERROR;
    std::string name = node.name();
    if (uppercaseTitle) {
        transform(name.begin(), name.end(), name.begin(), ::toupper);
    }
    if (description.empty()) {
        if (node.show_name() && !name.empty())
            builder.Write(name, wrapName);
    } else {
        bool includeName = false;
        if (!name.empty() && node.show_name()) {
            includeName = true;
            builder.Write(name, wrapName);
            if (node.show_separator())
                builder.Write(config.afterName, wrapName);
            builder.Write(
                    config.isNameOnOwnLine || description.find('\n') != std::string::npos ? "\n" : " ",
                    wrapName);
        }
        if (!is_single_line && builder.RequiresMultipleLines() && !builder.IsCurrentLineEmpty()) {
            // Make sure there is a break between the current line and next one if
            // there is not one already.
            builder.Write("\n");
        }
        if (includeName) {
            builder.IncrementPrefixOtherLines(
                    children.empty() ? config.propertyPrefixNoChildren : config.propertyPrefixIfChildren,
                    true);
        }

        if (uppercaseTitle) {
            transform(description.begin(), description.end(), description.begin(), ::toupper);
        }
        builder.Write(description, wrapDescription);

        if (!includeName) {
            builder.IncrementPrefixOtherLines(
                    children.empty() ? config.propertyPrefixNoChildren : config.propertyPrefixIfChildren,
                    false);
        }
    }
    if (!config.suffixLineOne.empty()) {
        builder.WriteStretched(config.suffixLineOne, builder.wrap_width());
    }
    std::vector<DiagnosticsNode*> propertiesIterable = node.GetProperties(); //.where(
    //(DiagnosticsNode n) => !n.isFiltered(_minLevel),
    //);
    std::vector<DiagnosticsNode*> properties;
    if (max_descendents_truncatable_node_ >= 0 && node.AllowTruncate()) {
        if (propertiesIterable.size() < max_descendents_truncatable_node_) {
            //properties =
            //        propertiesIterable.take(max_descendents_truncatable_node_).toList();
            //properties.emplace_back(DiagnosticsNode.message('...'));
        } else {
            //properties = propertiesIterable.toList();
        }
        if (max_descendents_truncatable_node_ < children.size()) {
            //children = children.take(max_descendents_truncatable_node_).toList();
            //children.add(DiagnosticsNode.message('...'));
        }
    } else {
        //properties = propertiesIterable.toList();
    }

    // If the node does not show a separator and there is no description then
    // we should not place a separator between the name and the value.
    // Essentially in this case the properties are treated a bit like a value.
    if ((!properties.empty() || !children.empty() || !node.EmptyBodyDescription().empty()) &&
        (node.show_separator() || !description.empty())) {
        builder.Write(config.afterDescriptionIfBody);
    }

    if (config.lineBreakProperties)
        builder.Write(config.lineBreak);

    if (!properties.empty())
        builder.Write(config.beforeProperties);

    builder.IncrementPrefixOtherLines(config.bodyIndent, false);

    if (!node.EmptyBodyDescription().empty() &&
        properties.empty() &&
        children.empty() &&
        !prefixLineOne.empty()) {
        builder.Write(node.EmptyBodyDescription());
        if (config.lineBreakProperties)
            builder.Write(config.lineBreak);
    }

    for (int i = 0; i < properties.size(); ++i) {
        DiagnosticsNode* property = properties[i];
        if (i > 0)
            builder.Write(config.propertySeparator);

        TextTreeConfiguration propertyStyle = property->GetTextTreeConfiguration();
        if (IsSingleLine(property->style())) {
            // We have to treat single line properties slightly differently to deal
            // with cases where a single line properties output may not have single
            // linebreak.
            std::string propertyRender = Render(*property,
                                                propertyStyle.prefixLineOne,
                                                "${propertyStyle.childLinkSpace}${propertyStyle.prefixOtherLines}",
                                                config);
            std::vector<std::string> propertyLines; // = propertyRender.split('\n');
            if (propertyLines.size() == 1 && !config.lineBreakProperties) {
                builder.Write(propertyLines.front());
            } else {
                builder.Write(propertyRender);
                if (!propertyRender.ends_with('\n'))
                    builder.Write("\n");
            }
        } else {
            std::string propertyRender = Render(*property,
                                                "${builder.prefixOtherLines}${propertyStyle.prefixLineOne}",
                                                "${builder.prefixOtherLines}${propertyStyle.childLinkSpace}${propertyStyle.prefixOtherLines}",
                                                config);
            builder.WriteRawLines(propertyRender);
        }
    }
    if (!properties.empty())
        builder.Write(config.afterProperties);

    builder.Write(config.mandatoryAfterProperties);

    if (!config.lineBreakProperties)
        builder.Write(config.lineBreak);

    std::string prefixChildren = config.bodyIndent;
    std::string prefixChildrenRaw = "$prefixOtherLines$prefixChildren";
    if (children.empty() &&
        config.addBlankLineIfNoChildren &&
        builder.RequiresMultipleLines()// &&
        //builder.prefixOtherLines!.trimRight().isNotEmpty
    ) {
        builder.Write(config.lineBreak);
    }

    if (!children.empty() && config.showChildren) {
        if (config.isBlankLineBetweenPropertiesAndChildren &&
            !properties.empty() &&
            children.front()->GetTextTreeConfiguration().isBlankLineBetweenPropertiesAndChildren) {
            builder.Write(config.lineBreak);
        }

        builder.prefix_other_lines() = prefixOtherLines;

        for (int i = 0; i < children.size(); i++) {
            DiagnosticsNode* child = children[i];
            FML_CHECK(child != nullptr);
            TextTreeConfiguration childConfig = ChildTextConfiguration(*child, config);
            if (i == children.size() - 1) {
                std::string lastChildPrefixLineOne = "$prefixChildrenRaw${childConfig.prefixLastChildLineOne}";
                std::string childPrefixOtherLines = "$prefixChildrenRaw${childConfig.childLinkSpace}${childConfig.prefixOtherLines}";
                builder.WriteRawLines(Render(*child,
                                             lastChildPrefixLineOne,
                                             childPrefixOtherLines,
                                             config));
                if (!childConfig.footer.empty()) {
                    builder.prefix_other_lines() = prefixChildrenRaw;
                    builder.Write("${childConfig.childLinkSpace}${childConfig.footer}");
                    if (!childConfig.mandatoryFooter.empty()) {
                        builder.WriteStretched(
                                childConfig.mandatoryFooter,
                                std::max(builder.wrap_width(), static_cast<int>(wrap_width_properties_ + childPrefixOtherLines.size())));
                    }
                    builder.Write(config.lineBreak);
                }
            } else {
                TextTreeConfiguration nextChildStyle = ChildTextConfiguration(*children[i + 1], config);
                std::string childPrefixLineOne = "$prefixChildrenRaw${childConfig.prefixLineOne}";
                std::string childPrefixOtherLines ="$prefixChildrenRaw${nextChildStyle.linkCharacter}${childConfig.prefixOtherLines}";
                builder.WriteRawLines(Render(
                        *child,
                        childPrefixLineOne,
                        childPrefixOtherLines,
                        config));
                if (!childConfig.footer.empty()) {
                    builder.prefix_other_lines() = prefixChildrenRaw;
                    builder.Write("${childConfig.linkCharacter}${childConfig.footer}");
                    if (!childConfig.mandatoryFooter.empty()) {
                        builder.WriteStretched(
                                childConfig.mandatoryFooter,
                                std::max(builder.wrap_width(), static_cast<int>(wrap_width_properties_ + childPrefixOtherLines.size())));
                    }
                    builder.Write(config.lineBreak);
                }
            }
        }
    }
    //if (parentConfiguration == null && config.mandatoryFooter.isNotEmpty) {
    if (!config.mandatoryFooter.empty()) {
        builder.WriteStretched(config.mandatoryFooter, builder.wrap_width());
        builder.Write(config.lineBreak);
    }
    return builder.Build();
}
} // namespace sm