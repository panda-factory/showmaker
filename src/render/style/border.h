//
// Created by guozhenxiong on 2021-08-07.
//

#ifndef SHOWMAKER_BORDER_H
#define SHOWMAKER_BORDER_H

#include "render/style/line.h"
namespace sm {
struct Border : public Line {
    SkScalar radius = 0;
};
} // namespace sm

#endif //SHOWMAKER_BORDER_H
