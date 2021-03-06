//
// Created by guozhenxiong on 2021-08-22.
//

#ifndef SHOWMAKER_PAINT_CONTEXT_H
#define SHOWMAKER_PAINT_CONTEXT_H

#include "render/painting/picture_recorder.h"
#include "render/layer/container_layer.h"
#include "render/layer/picture_layer.h"

namespace sm {
class RenderObject;

class PaintContext {
public:
    static void RepaintCompositedChild(RenderObject* child);

    void AppendLayer(std::shared_ptr<ContainerLayer> layer) const;

    void PaintChild(RenderObject* child, Position offset) const;

    SkCanvas *canvas();

    explicit PaintContext(const SkRect &bounds, ContainerLayer *container);

    ~PaintContext();

private:
    void CompositeChild(RenderObject* child, Position offset) const;

    bool is_recording_;

    PictureRecorder recorder_;

    SkRect bounds_;

    SkCanvas *canvas_;

    ContainerLayer *container_;

    PictureLayer *picture_layer_;
};
} // namespace sm

#endif //SHOWMAKER_PAINT_CONTEXT_H
