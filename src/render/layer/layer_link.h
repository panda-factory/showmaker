//
// Created by guozhenxiong on 2021-10-30.
//

#ifndef SHOWMAKER_LAYER_LINK_H
#define SHOWMAKER_LAYER_LINK_H

#include <string>

namespace sm {
class LeaderLayer;
class LayerLink {
public:
    std::string ToString();

private:
    size_t leader_size_;

    LeaderLayer* leader_;
};
} // namespace sm

#endif //SHOWMAKER_LAYER_LINK_H
