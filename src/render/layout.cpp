//
// Created by guozhenxiong on 2021-08-04.
//

#include "layout.h"


void Layout::Draw(SkCanvas* canvas)
{
    // Clear background
    canvas->clear(SK_ColorWHITE);
    auto child_offsets = CalculateChildOffsets(canvas);

    for(std::size_t i = 0; i < children_.size(); ++i)
    {
        children_[i]->SetPosition(child_offsets[i]);
        children_[i]->Draw(canvas);
    }
}