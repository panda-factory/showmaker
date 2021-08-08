//
// Created by guozhenxiong on 2021-08-07.
//

#ifndef XXX_CANVAS_SCOPE_H
#define XXX_CANVAS_SCOPE_H

#include <optional>

#include "render/clipping_box.h"

#include <third-party/skia/include/core/SkCanvas.h>

struct CanvasScope {
    CanvasScope(SkCanvas* canvas, const std::optional<ClippingBox>& clipping_box);

    SkAutoCanvasRestore auto_restore;
};


#endif //XXX_CANVAS_SCOPE_H
