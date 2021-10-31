//
// Created by guozhenxiong on 2021-10-31.
//

#ifndef SHOWMAKER_TEXT_TREE_CONFIGURATION_H
#define SHOWMAKER_TEXT_TREE_CONFIGURATION_H

#include <string>

namespace sm {
struct TextTreeConfiguration {

    /// Prefix to add to the first line to display a child with this style.
    const std::string prefixLineOne;

    /// Suffix to add to end of the first line to make its length match the footer.
    const std::string suffixLineOne;

    /// Prefix to add to other lines to display a child with this style.
    ///
    /// [prefixOtherLines] should typically be one character shorter than
    /// [prefixLineOne] is.
    const std::string prefixOtherLines;

    /// Prefix to add to the first line to display the last child of a node with
    /// this style.
    const std::string prefixLastChildLineOne;

    /// Additional prefix to add to other lines of a node if this is the root node
    /// of the tree.
    const std::string prefixOtherLinesRootNode;

    /// Prefix to add before each property if the node as children.
    ///
    /// Plays a similar role to [linkCharacter] except that some configurations
    /// intentionally use a different line style than the [linkCharacter].
    const std::string propertyPrefixIfChildren;

    /// Prefix to add before each property if the node does not have children.
    ///
    /// This string is typically a whitespace string the same length as
    /// [propertyPrefixIfChildren] but can have a different length.
    const std::string propertyPrefixNoChildren;

    /// Character to use to draw line linking parent to child.
    ///
    /// The first child does not require a line but all subsequent children do
    /// with the line drawn immediately before the left edge of the previous
    /// sibling.
    const std::string linkCharacter;

    /// Whitespace to draw instead of the childLink character if this node is the
    /// last child of its parent so no link line is required.
    const std::string childLinkSpace;

    /// Character(s) to use to separate lines.
    ///
    /// Typically leave set at the default value of '\n' unless this style needs
    /// to treat lines differently as is the case for
    /// [singleLineTextConfiguration].
    const std::string lineBreak;

    /// Whether to place line breaks between properties or to leave all
    /// properties on one line.
    const bool lineBreakProperties = true;


    /// Text added immediately before the name of the node.
    ///
    /// See [errorTextConfiguration] for an example of using this to achieve a
    /// custom line art style.
    const std::string beforeName;

    /// Text added immediately after the name of the node.
    ///
    /// See [transitionTextConfiguration] for an example of using a value other
    /// than ':' to achieve a custom line art style.
    const std::string afterName;

    /// Text to add immediately after the description line of a node with
    /// properties and/or children if the node has a body.
    const std::string afterDescriptionIfBody;

    /// Text to add immediately after the description line of a node with
    /// properties and/or children.
    const std::string afterDescription;

    /// Optional string to add before the properties of a node.
    ///
    /// Only displayed if the node has properties.
    /// See [singleLineTextConfiguration] for an example of using this field
    /// to enclose the property list with parenthesis.
    const std::string beforeProperties;

    /// Optional string to add after the properties of a node.
    ///
    /// See documentation for [beforeProperties].
    const std::string afterProperties;

    /// Mandatory string to add after the properties of a node regardless of
    /// whether the node has any properties.
    const std::string mandatoryAfterProperties;

    /// Property separator to add between properties.
    ///
    /// See [singleLineTextConfiguration] for an example of using this field
    /// to render properties as a comma separated list.
    const std::string propertySeparator;

    /// Prefix to add to all lines of the body of the tree node.
    ///
    /// The body is all content in the node other than the name and description.
    const std::string bodyIndent;

    /// Whether the children of a node should be shown.
    ///
    /// See [singleLineTextConfiguration] for an example of using this field to
    /// hide all children of a node.
    const bool showChildren;

    /// Whether to add a blank line at the end of the output for a node if it has
    /// no children.
    ///
    /// See [denseTextConfiguration] for an example of setting this to false.
    const bool addBlankLineIfNoChildren;

    /// Whether the name should be displayed on the same line as the description.
    const bool isNameOnOwnLine;

    /// Footer to add as its own line at the end of a non-root node.
    ///
    /// See [transitionTextConfiguration] for an example of using footer to draw a box
    /// around the node. [footer] is indented the same amount as [prefixOtherLines].
    const std::string footer;

    /// Footer to add even for root nodes.
    const std::string mandatoryFooter;

    /// Add a blank line between properties and children if both are present.
    const bool isBlankLineBetweenPropertiesAndChildren;

    static const TextTreeConfiguration DENSE_TEXT_CONFIGURATION;
    static const TextTreeConfiguration DASHED_TEXT_CONFIGURATION;
    static const TextTreeConfiguration SINGLE_LINE_TEXT_CONFIGURATION;
    static const TextTreeConfiguration SPARSE_TEXT_CONFIGURATION;

};
} // namespace sm

#endif //SHOWMAKER_TEXT_TREE_CONFIGURATION_H
