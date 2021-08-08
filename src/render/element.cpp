//
// Created by guozhenxiong on 2021-08-04.
//

#include "element.h"

void Element::Draw(SkCanvas *canvas, Drawable* drawable, const Position2D& position)
{
    drawable->Draw(canvas, position);
}