//
// Created by guozhenxiong on 2021-08-21.
//

#ifndef SHOWMAKER_VIEW_H
#define SHOWMAKER_VIEW_H

#include "element.h"

namespace sm {
class View : public Element {
public:
    void Paint(PaintContext *context) override;

    void PerformLayout() override;

    Size MeasureSize() override;
};
} // namespace sm

#endif //SHOWMAKER_VIEW_H
