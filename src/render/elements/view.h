//
// Created by guozhenxiong on 2021-08-21.
//

#ifndef SHOWMAKER_VIEW_H
#define SHOWMAKER_VIEW_H

#include "element.h"

namespace sm {
class RenderObject;
class View : public Element {
public:
    bool HitTest(double x, double y) override;

    void Paint(PaintContext *context) override;

    /// | RenderObject |
    void Paint(const PaintContext* context, Position offset) override;

    void PerformLayout() override;

    Size MeasureSize() override;
private:
    RenderObject* child_;
};
} // namespace sm

#endif //SHOWMAKER_VIEW_H
