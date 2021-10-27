//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef SHOWMAKER_LAYOUT_H
#define SHOWMAKER_LAYOUT_H

#include <vector>
#include <memory>
#include "render/elements/element.h"

namespace sm {
class Layout : public Element {
public:
    bool HitTest(double x, double y) override;

    void Paint(const PaintContext* context, Position offset) override;

    void Paint(PaintContext *context) override final;

    void PerformLayout() override;

protected:
    SkScalar spacing_;

private:
    virtual std::vector<Position> CalculateChildOffsets() const = 0;
};
} // namespace sm

#endif //SHOWMAKER_LAYOUT_H
