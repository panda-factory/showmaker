//
// Created by guozhenxiong on 2021-11-04.
//

#include "clip_rrect_layer.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {


ClipRRectLayer::ClipRRectLayer(const RRect& clip_rrect, Clip clip_behavior)
  : clip_rrect_(clip_rrect), clip_behavior_(clip_behavior)
{
    FML_CHECK(clip_behavior_ != Clip::NONE);
}

void ClipRRectLayer::SetClipRRect(const RRect& value)
{
    if (value != clip_rrect_) {
        clip_rrect_ = value;
        MarkNeedsAddToScene();
    }
}

void ClipRRectLayer::SetClipBehavior(const Clip& value)
{
    FML_CHECK(value != Clip::NONE);
    if (value != clip_behavior_) {
        clip_behavior_ = value;
        MarkNeedsAddToScene();
    }
}
} // namespace sm