//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_ELEMENT_H
#define XXX_ELEMENT_H

#include "render/position2d.h"
class SkSurface;
class Element {
public:
    virtual void Draw(SkSurface* surface) const = 0;

    inline void SetPosition(const Position2D& position) {position_ = position;}

protected:
    Position2D position_;

};


#endif //XXX_ELEMENT_H
