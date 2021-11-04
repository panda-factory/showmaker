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
} // namespace sm