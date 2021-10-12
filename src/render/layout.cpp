//
// Created by guozhenxiong on 2021-08-04.
//

#include "layout.h"

namespace sm {
void Layout::Paint(PaintContext *context)
{
}

void Layout::PerformLayout()
{
    auto child_offsets = CalculateChildOffsets();
}
} // namespace sm