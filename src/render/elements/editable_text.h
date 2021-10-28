//
// Created by guozhenxiong on 2021-10-25.
//

#ifndef SHOWMAKER_EDITABLE_TEXT_H
#define SHOWMAKER_EDITABLE_TEXT_H

#include "element.h"

#include "render/shape/text.h"
#include "render/shape/text/text_input_client.h"

namespace sm {
class EditableText : public Element, public TextInputClient {
public:
    /// | TextInputClient |
    void OnChar(const std::u16string& c) override;

    /// | Element |
    bool HitTest(double x, double y) override;

    /// | Element |
    void Paint(PaintContext *context) override;

    /// | Element |
    Size MeasureSize() override;

    /// | Element |
    void PerformLayout() override;

    /// | RenderObject |
    void Paint(const PaintContext* context, Position offset) override;

    EditableText(const std::string &text);

private:
    Text text_;

    bool blink_;
};
} // namespace sm

#endif //SHOWMAKER_EDITABLE_TEXT_H
