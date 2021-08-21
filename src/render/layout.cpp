//
// Created by guozhenxiong on 2021-08-04.
//

#include "layout.h"


void Layout::Draw(SkCanvas* canvas)
{
    // Clear background
    canvas->clear(SK_ColorWHITE);
    auto child_offsets = CalculateChildOffsets();

    for(std::size_t i = 0; i < children_.size(); ++i)
    {
        CompositeChild(children_[i].get(), canvas);
    }
}

void Layout::CompositeChild(Element* element, SkCanvas* canvas)
{
    element->Draw(canvas);

    layer_->Add(element->layer());
}

void Layout::PerformLayout()
{
    auto child_offsets = CalculateChildOffsets();
}