//
// Created by guozhenxiong on 2021-08-04.
//

#include "column.h"

namespace strg {
Size Column::MeasureSize()
{
    return {0, 0};
}

std::vector<Position> Column::CalculateChildOffsets() const
{
    std::vector<Position> offsets;
    offsets.reserve(children_.size());
    Position offset{0, 0};

    for (const auto &child : children_) {
        offsets.push_back(offset);
        child->SetPosition(offset);

        offset.y += child->MeasureSize().height + spacing_;
    }

    return offsets;
}
} // namespace strg