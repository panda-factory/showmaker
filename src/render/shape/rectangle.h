//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef SHOWMAKER_RECTANGLE_H
#define SHOWMAKER_RECTANGLE_H

#include "render/shape.h"
#include "graphics/size.h"

namespace sm {
class Rectangle : public Shape {
public:
    void Draw(SkCanvas *, const Position &position) override;

    Rectangle(const Size &size);

private:
    Size size_;
};
} // namespace sm

#endif //SHOWMAKER_RECTANGLE_H
