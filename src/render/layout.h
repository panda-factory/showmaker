//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef STRUGGLE_LAYOUT_H
#define STRUGGLE_LAYOUT_H

#include <vector>
#include <memory>
#include "render/elements/element.h"

namespace strg {
class Layout : public Element {
public:
    void Paint(PaintContext *context) override final;

    void PerformLayout() override;

protected:
    SkScalar spacing_;

private:
    virtual std::vector<Position> CalculateChildOffsets() const = 0;
};
} // namespace strg

#endif //STRUGGLE_LAYOUT_H
