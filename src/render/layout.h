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
    void Draw(SkSurface* surface) override final;

    inline void AddElement(std::unique_ptr<Element> element) {
        children_.push_back(std::move(element));
    }

protected:
    std::vector<std::unique_ptr<Element>> children_;

    SkScalar spacing_;
private:

    virtual std::vector<Position2D> CalculateChildOffsets(SkCanvas* canvas) const = 0;
};


#endif //XXX_LAYOUT_H