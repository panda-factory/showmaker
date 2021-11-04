//
// Created by guozhenxiong on 2021-11-04.
//

#ifndef SHOWMAKER_CLIP_RRECT_LAYER_H
#define SHOWMAKER_CLIP_RRECT_LAYER_H

#include "render/layer/container_layer.h"
#include "graphics/rrect.h"
#include "render/painting/clip.h"

namespace sm {
class ClipRRectLayer : public ContainerLayer {
public:
    void SetClipRRect(const RRect& value);

    void SetClipBehavior(const Clip& value);

    ClipRRectLayer(const RRect& clip_rrect, Clip clip_behavior = Clip::ANTI_ALIAS);

private:
    RRect clip_rrect_;

    Clip clip_behavior_;
};
} // namespace sm

#endif //SHOWMAKER_CLIP_RRECT_LAYER_H
