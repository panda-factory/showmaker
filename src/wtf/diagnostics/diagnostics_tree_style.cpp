//
// Created by guozhenxiong on 2021-10-31.
//
#include "diagnostics_tree_style.h"
namespace sm {
bool IsSingleLine(const DiagnosticsTreeStyle& style) {
    return style == DiagnosticsTreeStyle::SINGLE_LINE;
}
} // namespace sm