//
// Created by guozhenxiong on 2021-08-07.
//

#ifndef STRUGGLE_BORDER_H
#define STRUGGLE_BORDER_H

#include "render/style/line.h"
namespace strg {
struct Border : public Line {
    SkScalar radius = 0;
};
} // namespace strg

#endif //STRUGGLE_BORDER_H
