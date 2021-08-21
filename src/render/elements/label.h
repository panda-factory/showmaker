//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_LABEL_H
#define XXX_LABEL_H

#include "render/element.h"
#include "render/shape/text.h"

class Label : public Element {
public:
    void Draw(SkCanvas* canvas) override;

    Size2D MeasureSize() override;

    explicit Label(const std::string& text);

    ~Label() = default;

private:
    Text text_;
};


#endif //XXX_LABEL_H
