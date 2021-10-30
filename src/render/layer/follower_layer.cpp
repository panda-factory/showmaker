//
// Created by guozhenxiong on 2021-10-30.
//

#include "follower_layer.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

FollowerLayer::FollowerLayer(LayerLink* link)
  : link_(link)
{
    FML_CHECK(link != nullptr);
}
}