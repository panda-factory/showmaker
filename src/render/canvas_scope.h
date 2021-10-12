//
// Created by guozhenxiong on 2021-08-07.
//

#ifndef SHOWMAKER_CANVAS_SCOPE_H
#define SHOWMAKER_CANVAS_SCOPE_H

#include <optional>

#include "render/clipping_box.h"

#include <third_party/skia/include/core/SkCanvas.h>
namespace sm {
struct CanvasScope {
    CanvasScope(SkCanvas *canvas, const std::optional<ClippingBox> &clipping_box);

    SkAutoCanvasRestore auto_restore;
};
} // namespace sm

#endif //SHOWMAKER_CANVAS_SCOPE_H
