//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_ELEMENT_H
#define XXX_ELEMENT_H

#include <vector>

#include "render/position2d.h"
#include "render/drawable.h"
#include "render/size.h"

#include "include/core/SkSurface.h"
#include "include/core/SkCanvas.h"

class Element {
public:
    virtual void Draw(SkSurface* surface) = 0;

    inline void SetPosition(const Position2D& position) {position_ = position;}

    virtual Size2D MeasureSize(SkCanvas* canvas) = 0;

    virtual ~Element() = default;
protected:
    void Draw(SkCanvas* canvas, Drawable* drawable, const Position2D& position);

    Position2D position_;
private:
};


#endif //XXX_ELEMENT_H
