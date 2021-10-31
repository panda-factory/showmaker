//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_DIAGNOSTICS_TREE_STYLE_H
#define SHOWMAKER_DIAGNOSTICS_TREE_STYLE_H

namespace sm {
enum class DiagnosticsTreeStyle {
    /// A style that does not display the tree, for release mode.
    NONE,

    /// Sparse style for displaying trees.
    ///
    /// See also:
    ///
    ///  * [RenderObject], which uses this style.
    SPARSE,

    /// Connects a node to its parent with a dashed line.
    ///
    /// See also:
    ///
    ///  * [RenderSliverMultiBoxAdaptor], which uses this style to distinguish
    ///    offstage children from onstage children.
    OFFSTAGE,

    /// Slightly more compact version of the [sparse] style.
    ///
    /// See also:
    ///
    ///  * [Element], which uses this style.
    DENSE,

    /// Style that enables transitioning from nodes of one style to children of
    /// another.
    ///
    /// See also:
    ///
    ///  * [RenderParagraph], which uses this style to display a [TextSpan] child
    ///    in a way that is compatible with the [DiagnosticsTreeStyle.sparse]
    ///    style of the [RenderObject] tree.
    TRANSITION,

    /// Style for displaying content describing an error.
    ///
    /// See also:
    ///
    ///  * [FlutterError], which uses this style for the root node in a tree
    ///    describing an error.
    ERROR,

    /// Render the tree just using whitespace without connecting parents to
    /// children using lines.
    ///
    /// See also:
    ///
    ///  * [SliverGeometry], which uses this style.
    WHITE_SPACE,

    /// Render the tree without indenting children at all.
    ///
    /// See also:
    ///
    ///  * [DiagnosticsStackTrace], which uses this style.
    FLAT,

    /// Render the tree on a single line without showing children.
    SINGLE_LINE,

    /// Render the tree using a style appropriate for properties that are part
    /// of an error message.
    ///
    /// The name is placed on one line with the value and properties placed on
    /// the following line.
    ///
    /// See also:
    ///
    ///  * [singleLine], which displays the same information but keeps the
    ///    property and value on the same line.
    ERROR_PROPERTY,

    /// Render only the immediate properties of a node instead of the full tree.
    ///
    /// See also:
    ///
    ///  * [DebugOverflowIndicatorMixin], which uses this style to display just
    ///    the immediate children of a node.
    SHALLOW,

    /// Render only the children of a node truncating before the tree becomes too
    /// large.
    TRUNCATE_CHILDREN,
};

bool IsSingleLine(const DiagnosticsTreeStyle& style);
} // namespace sm

#endif //SHOWMAKER_DIAGNOSTICS_TREE_STYLE_H
