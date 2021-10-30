//
// Created by guozhenxiong on 2021-10-30.
//

#include "layer_link.h"

namespace sm {
std::string LayerLink::ToString()
{
    return leader_ == nullptr ? "<linked>" : "<dangling>";
}
} // namespace sm