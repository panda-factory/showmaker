//
// Created by guozhenxiong on 2021-10-31.
//

#include "text_tree_configuration.h"
namespace sm {

const TextTreeConfiguration TextTreeConfiguration::DASHED_TEXT_CONFIGURATION = {
        .prefixLineOne =            "╎╌",
        .prefixOtherLines =         " ",
        .prefixLastChildLineOne =   "└╌",
        // Intentionally not set as a dashed line as that would make the properties
        // look like they were disabled.
        .prefixOtherLinesRootNode = " ",
        .propertyPrefixIfChildren = "│ ",
        .propertyPrefixNoChildren = "  ",
        .linkCharacter =            "╎",
};

const TextTreeConfiguration TextTreeConfiguration::DENSE_TEXT_CONFIGURATION = {
        .prefixLineOne = "├",
        .prefixOtherLines =         "",
        .prefixLastChildLineOne =   "└",
        .prefixOtherLinesRootNode = "",
        .propertyPrefixIfChildren = "│",
        .propertyPrefixNoChildren = " ",
        .linkCharacter =            "│",
        .lineBreakProperties = false,
        .beforeProperties = "(",
        .afterProperties = ")",
        .propertySeparator = ", ",
        .addBlankLineIfNoChildren = false,
        .isBlankLineBetweenPropertiesAndChildren = false,
};

const TextTreeConfiguration TextTreeConfiguration::SINGLE_LINE_TEXT_CONFIGURATION = {
        .prefixLineOne = "",
        .prefixOtherLines = "",
        .prefixLastChildLineOne = "",
        .prefixOtherLinesRootNode = "",
        .propertyPrefixIfChildren = "  ",
        .propertyPrefixNoChildren = "  ",
        .linkCharacter = "",
        .lineBreak = "",
        .lineBreakProperties = false,
        .beforeProperties = "(",
        .afterProperties = ")",
        .propertySeparator = ", ",
        .showChildren = false,
        .addBlankLineIfNoChildren = false,
};

const TextTreeConfiguration TextTreeConfiguration::SPARSE_TEXT_CONFIGURATION = {
        .prefixLineOne =            "├─",
        .prefixOtherLines =         " ",
        .prefixLastChildLineOne =   "└─",
        .prefixOtherLinesRootNode = " ",
        .propertyPrefixIfChildren = "│ ",
        .propertyPrefixNoChildren = "  ",
        .linkCharacter =            "│",
};

} // namespace sm