//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef SHOWMAKER_TEXT_H
#define SHOWMAKER_TEXT_H

#include "render/shape.h"
#include "graphics/size.h"

#include "text/paragraph.h"
#include "text/text_editing_value.h"

#include <third_party/skia/include/core/SkFont.h>

namespace sm {
class Text : public Shape {
public:
    SkRect GetLocation();

    size_t GetPosition(double x, double y);

    inline TextEditingValue& text() { return text_; }

    void Draw(SkCanvas *, const Position &position) override;

    Size MeasureSize();

    Text();

    Text(const std::string &text);

private:
    TextEditingValue text_;

    SkFont font_;

    SkScalar size_ = 12;

    std::unique_ptr<Paragraph> paragraph_;
};
} // namespace sm

#endif //SHOWMAKER_TEXT_H
