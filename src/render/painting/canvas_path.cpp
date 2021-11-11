//
// Created by guozhenxiong on 2021-11-04.
//

#include "canvas_path.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

void CanvasPath::AddRect(const Rect& rect)
{
    FML_CHECK(rect.IsValid());
}

/// Rect::operator!=
bool operator != (const CanvasPath& path1, const CanvasPath& path2)
{
    if (1) {
        return true;
    } else {
        return false;
    }
}
} // namespace sm