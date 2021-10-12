//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef SHOWMAKER_TEXT_H
#define SHOWMAKER_TEXT_H

#include "render/shape.h"
#include "graphics/size.h"

#include "text/paragraph.h"

#include <third_party/skia/include/core/SkFont.h>

namespace sm {
class Text : public Shape {
public:
    void Draw(SkCanvas *, const Position &position) override;

    Size MeasureSize();

    Text(const std::string &text);

private:
    std::string text_;

    SkFont font_;

    SkScalar size_ = 12;

    std::unique_ptr<Paragraph> paragraph_;
};
} // namespace sm

#endif //SHOWMAKER_TEXT_H
