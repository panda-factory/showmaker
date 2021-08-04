//
// Created by guozhenxiong on 2021-08-04.
//

#include "layout.h"


void Layout::Draw(SkSurface* surface) const
{

    for(std::size_t i = 0; i < children_.size(); ++i)
    {
        children_[i]->SetPosition({30, 30});
        children_[i]->Draw(surface);
    }
}