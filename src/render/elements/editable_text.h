//
// Created by guozhenxiong on 2021-10-25.
//

#ifndef SHOWMAKER_EDITABLE_TEXT_H
#define SHOWMAKER_EDITABLE_TEXT_H

#include "element.h"

#include "render/shape/text.h"

namespace sm {
class EditableText : public Element{
public:
    bool HitTest(double x, double y) override;

    void Paint(PaintContext *context) override;

    Size MeasureSize() override;

    EditableText(const std::string &text);

private:
    Text text_;

    bool blink_;
};
} // namespace sm

#endif //SHOWMAKER_EDITABLE_TEXT_H
