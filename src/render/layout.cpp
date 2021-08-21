//
// Created by guozhenxiong on 2021-08-04.
//

#include "layout.h"


void Layout::Draw(SkCanvas* canvas)
{
    for(std::size_t i = 0; i < children_.size(); ++i)
    {
        PaintChild(children_[i].get(), canvas);
    }
}

void Layout::PerformLayout()
{
    auto child_offsets = CalculateChildOffsets();
}