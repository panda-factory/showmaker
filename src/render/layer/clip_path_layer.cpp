//
// Created by guozhenxiong on 2021-11-04.
//

#include "clip_path_layer.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {
ClipPathLayer::ClipPathLayer(const Path& clip_path, const Clip& clip_behavior)
  : clip_path_(clip_path), clip_behavior_(clip_behavior)
{
    FML_CHECK(clip_behavior_ != Clip::NONE);
}

void ClipPathLayer::SetClipPath(const Path& path)
{
    if (path != clip_path_) {
        clip_path_ = path;
        MarkNeedsAddToScene();
    }
}
} // namespace sm