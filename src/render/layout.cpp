//
// Created by guozhenxiong on 2021-08-04.
//

#include "layout.h"


void Layout::Paint(PaintContext* context)
{
    for(std::size_t i = 0; i < children_.size(); ++i)
    {
        PaintChild(children_[i].get(), nullptr);
    }
}

void Layout::PerformLayout()
{
    auto child_offsets = CalculateChildOffsets();
}