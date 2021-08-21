//
// Created by guozhenxiong on 2021-08-21.
//

#ifndef XXX_VIEW_H
#define XXX_VIEW_H

#include "render/element.h"

class View : public Element {
public:
    void Draw(SkCanvas* canvas) override;

    void PerformLayout() override;

    Size2D MeasureSize() override;
};


#endif //XXX_VIEW_H
