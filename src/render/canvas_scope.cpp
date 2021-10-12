//
// Created by guozhenxiong on 2021-08-07.
//

#include "canvas_scope.h"
namespace sm {
CanvasScope::CanvasScope(SkCanvas *canvas, const std::optional<ClippingBox> &clipping_box)
        : auto_restore(canvas, clipping_box.has_value())
{
    if (clipping_box) {
        canvas->clipRect(SkRect::MakeXYWH(clipping_box->top_left.x,
                                          clipping_box->top_left.y,
                                          clipping_box->size.width,
                                          clipping_box->size.height));
    }
}
} // namespace sm