//
// Created by guozhenxiong on 2021-11-04.
//

#ifndef SHOWMAKER_CLIP_PATH_LAYER_H
#define SHOWMAKER_CLIP_PATH_LAYER_H

#include "render/layer/container_layer.h"
#include "render/painting/canvas_path.h"
#include "render/painting/clip.h"

namespace sm {
class ClipPathLayer : public ContainerLayer {
public:
    void SetClipPath(const Path& path);

    ClipPathLayer(const Path& clip_path, const Clip& clip_behavior = Clip::ANTI_ALIAS);

private:
    Path clip_path_;

    Clip clip_behavior_;
};
} // namespace sm

#endif //SHOWMAKER_CLIP_PATH_LAYER_H
