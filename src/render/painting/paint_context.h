//
// Created by guozhenxiong on 2021-08-22.
//

#ifndef SHOWMAKER_PAINT_CONTEXT_H
#define SHOWMAKER_PAINT_CONTEXT_H

#include "render/painting/picture_recorder.h"
#include "render/layer/container_layer.h"
#include "render/layer/picture_layer.h"

namespace sm {
class PaintContext {
public:
    SkCanvas *canvas();

    explicit PaintContext(const SkRect &bounds, ContainerLayer *container);

    ~PaintContext();

private:
    bool is_recording_;

    PictureRecorder recorder_;

    SkRect bounds_;

    SkCanvas *canvas_;

    ContainerLayer *container_;

    PictureLayer *picture_layer_;
};
} // namespace sm

#endif //SHOWMAKER_PAINT_CONTEXT_H
