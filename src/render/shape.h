//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef SHOWMAKER_SHAPE_H
#define SHOWMAKER_SHAPE_H

#include "drawable.h"
#include "style/border.h"

namespace sm {
class Shape : public Drawable {
public:
    Shape();

protected:
    Border border_;
};
} // namespace sm

#endif //SHOWMAKER_SHAPE_H
