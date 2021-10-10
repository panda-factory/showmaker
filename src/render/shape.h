//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef STRUGGLE_SHAPE_H
#define STRUGGLE_SHAPE_H

#include "drawable.h"
#include "style/border.h"

namespace strg {
class Shape : public Drawable {
public:
    Shape();

protected:
    Border border_;
};
} // namespace strg

#endif //STRUGGLE_SHAPE_H
