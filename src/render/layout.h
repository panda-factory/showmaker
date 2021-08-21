//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_LAYOUT_H
#define XXX_LAYOUT_H

#include <vector>
#include <memory>
#include "element.h"
class Layout : public Element {
public:
    void Draw(SkCanvas* canvas) override final;

    void PerformLayout() override;

protected:
    SkScalar spacing_;

private:
    virtual std::vector<Position2D> CalculateChildOffsets() const = 0;
};


#endif //XXX_LAYOUT_H
