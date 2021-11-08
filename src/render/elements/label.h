//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef SHOWMAKER_LABEL_H
#define SHOWMAKER_LABEL_H

#include "element.h"
#include "render/shape/text.h"

namespace sm {
class Label : public Element {
public:
    /// | RenderObject |
    void Paint(const PaintContext* context, Position offset) override;

    void Paint(PaintContext *context) override;

    Size MeasureSize() override;

    explicit Label(const std::string &text);

    ~Label() = default;

private:
    Text text_;
};
} // namespace sm

#endif //SHOWMAKER_LABEL_H
