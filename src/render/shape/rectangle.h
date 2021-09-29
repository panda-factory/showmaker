//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef STRUGGLE_RECTANGLE_H
#define STRUGGLE_RECTANGLE_H

#include "render/shape.h"
#include "render/size.h"

namespace strg {
class Rectangle : public Shape {
public:
    void Draw(SkCanvas *, const Position2D &position) override;

    Rectangle(const Size2D &size);

private:
    Size2D size_;
};
} // namespace strg

#endif //STRUGGLE_RECTANGLE_H
