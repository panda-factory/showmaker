//
// Created by guozhenxiong on 2021-10-31.
//

#ifndef SHOWMAKER_CLIP_RECT_LAYER_H
#define SHOWMAKER_CLIP_RECT_LAYER_H

#include "render/layer/container_layer.h"
#include "graphics/rect.h"
#include "render/painting/clip.h"

namespace sm {
class ClipRectLayer : public ContainerLayer {
public:
    void SetClipRect(const Rect& value);

    void SetClipBehavior(const Clip& value);

    ClipRectLayer() = default;

    ClipRectLayer(Rect clip_rect, Clip clip_behavior = Clip::HARD_EDGE);

private:
    Rect clip_rect_;

    Clip clip_behavior_;
};
} // namespace sm

#endif //SHOWMAKER_CLIP_RECT_LAYER_H
