//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef SHOWMAKER_COLUMN_H
#define SHOWMAKER_COLUMN_H

#include "render/layout.h"
namespace sm {
class Column : public Layout {
protected:
    Size MeasureSize() override;

private:
    std::vector<Position> CalculateChildOffsets() const override;
};
} // namespace sm

#endif //SHOWMAKER_COLUMN_H
