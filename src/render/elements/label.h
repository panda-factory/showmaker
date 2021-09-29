//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef STRUGGLE_LABEL_H
#define STRUGGLE_LABEL_H

#include "element.h"
#include "render/shape/text.h"

namespace strg {
class Label : public Element {
public:
    void Paint(PaintContext *context) override;

    Size2D MeasureSize() override;

    explicit Label(const std::string &text);

    ~Label() = default;

private:
    Text text_;
};
} // namespace strg

#endif //STRUGGLE_LABEL_H
