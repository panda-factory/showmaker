//
// Created by guozhenxiong on 2021-10-31.
//

#include "clip_rect_layer.h"
#include <third_party/flutter/fml/logging.h>

namespace sm {

ClipRectLayer::ClipRectLayer(Rect clip_rect, Clip clip_behavior)
  : clip_rect_(clip_rect), clip_behavior_(clip_behavior)
{
    FML_CHECK(clip_behavior_ != Clip::NONE);
}

void ClipRectLayer::SetClipRect(const Rect& value)
{
    if (value != clip_rect_) {
        clip_rect_ = value;
        MarkNeedsAddToScene();
    }
}

void ClipRectLayer::SetClipBehavior(const Clip& value)
{
    FML_CHECK(value != Clip::NONE);
    if (value != clip_behavior_) {
        clip_behavior_ = value;
        MarkNeedsAddToScene();
    }
}
}