//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef XXX_TEXT_H
#define XXX_TEXT_H

#include "render/shape.h"
#include "render/size.h"

#include <third_party/skia/include/core/SkFont.h>

class Text : public Shape {
public:
    void Draw(SkCanvas*, const Position2D& position) override;

    Size2D MeasureSize();

    Text(const std::string& text);
private:
    std::string text_;

    SkFont font_;

    SkScalar size_ = 12;
};


#endif //XXX_TEXT_H
