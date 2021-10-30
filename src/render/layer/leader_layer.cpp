//
// Created by guozhenxiong on 2021-10-30.
//

#include "leader_layer.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {

LeaderLayer::LeaderLayer(LayerLink* link, Offset offset)
  : offset_(offset), link_(link)
{
    FML_CHECK(link != nullptr);
}

} // namespace sm