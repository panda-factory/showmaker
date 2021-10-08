//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef STRUGGLE_TEXT_H
#define STRUGGLE_TEXT_H

#include "render/shape.h"
#include "render/size.h"

#include <third_party/skia/include/core/SkFont.h>
#include <third_party/flutter/third_party/txt/src/txt/paragraph.h>

namespace strg {
class Text : public Shape {
public:
    void Draw(SkCanvas *, const Position2D &position) override;

    Size2D MeasureSize();

    Text(const std::string &text);

private:
    std::string text_;

    SkFont font_;

    SkScalar size_ = 12;

    std::unique_ptr<txt::Paragraph> paragraph_;
};
} // namespace strg

#endif //STRUGGLE_TEXT_H
