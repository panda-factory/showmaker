//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_SHAPE_H
#define XXX_SHAPE_H

#include "drawable.h"
#include "style/border.h"

class Shape : public Drawable {
public:
    Shape();

protected:
    Border border_;
};


#endif //XXX_SHAPE_H
