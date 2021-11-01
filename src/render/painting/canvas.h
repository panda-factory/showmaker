//
// Created by guozhenxiong on 2021-11-01.
//

#ifndef SHOWMAKER_CANVAS_H
#define SHOWMAKER_CANVAS_H

#include "graphics/rect.h"

#include "third_party/skia/include/core/SkCanvas.h"

namespace sm {
class PictureRecorder;

class Canvas {
public:
    Canvas(PictureRecorder* recorder, Rect cullRect = Rect::LARGEST);

private:
    PictureRecorder* recorder_;

    SkCanvas *canvas_;
};
} // namespace sm

#endif //SHOWMAKER_CANVAS_H
