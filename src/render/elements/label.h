//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_LABEL_H
#define XXX_LABEL_H

#include "render/element.h"
#include "render/shape/text.h"

class Label : public Element {
public:
    void Draw(SkSurface* surface) override;

    Size2D MeasureSize(SkCanvas* canvas) override;

    explicit Label(const std::string& text);

    ~Label() = default;

private:
    Text text_;
};


#endif //XXX_LABEL_H
