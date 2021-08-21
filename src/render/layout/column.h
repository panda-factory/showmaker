//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_COLUMN_H
#define XXX_COLUMN_H

#include "render/layout.h"
class Column : public Layout {
protected:
    Size2D MeasureSize() override;

private:
    std::vector<Position2D> CalculateChildOffsets() const override;
};


#endif //XXX_COLUMN_H
