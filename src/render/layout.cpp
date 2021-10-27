//
// Created by guozhenxiong on 2021-08-04.
//

#include "layout.h"

namespace sm {
bool Layout::HitTest(double x, double y)
{
    for (const auto& child : children_) {
        child->HitTest(x, y);
    }
    return false;
}

void Layout::Paint(const PaintContext* context, Position offset)
{
    for (std::size_t i = 0; i < children_.size(); ++i) {
        context->PaintChild(children_[0].get(), offset);
    }
}

void Layout::Paint(PaintContext *context)
{
}

void Layout::PerformLayout()
{
    auto child_offsets = CalculateChildOffsets();
}
} // namespace sm