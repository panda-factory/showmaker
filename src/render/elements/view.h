//
// Created by guozhenxiong on 2021-08-21.
//

#ifndef STRUGGLE_VIEW_H
#define STRUGGLE_VIEW_H

#include "element.h"

namespace strg {
class View : public Element {
public:
    void Paint(PaintContext *context) override;

    void PerformLayout() override;

    Size2D MeasureSize() override;
};
} // namespace strg

#endif //STRUGGLE_VIEW_H
