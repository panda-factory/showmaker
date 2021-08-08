//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef XXX_RECTANGLE_H
#define XXX_RECTANGLE_H

#include "render/shape.h"
#include "render/size.h"

class Rectangle : public Shape {
public:
    void Draw(SkCanvas*, const Position2D& position) override;

    Rectangle(const Size2D& size);

private:
    Size2D size_;
};


#endif //XXX_RECTANGLE_H
