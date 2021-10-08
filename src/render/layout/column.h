//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef STRUGGLE_COLUMN_H
#define STRUGGLE_COLUMN_H

#include "render/layout.h"
namespace strg {
class Column : public Layout {
protected:
    Size2D MeasureSize() override;

private:
    std::vector<Position2D> CalculateChildOffsets() const override;
};
} // namespace strg

#endif //STRUGGLE_COLUMN_H
