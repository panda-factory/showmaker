//
// Created by guozhenxiong on 2021-08-04.
//

#include "column.h"

Size2D Column::MeasureSize(SkCanvas* canvas)
{
    return {0, 0};
}

std::vector<Position2D> Column::CalculateChildOffsets(SkCanvas* canvas) const
{
    std::vector<Position2D> offsets;
    offsets.reserve(children_.size());
    Position2D offset{0, 0};

    for(const auto& child : children_)
    {
        offsets.push_back(offset);

        offset.y += child->MeasureSize(canvas).height + spacing_;
    }

    return offsets;
}