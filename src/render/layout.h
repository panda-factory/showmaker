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
    void Draw(SkSurface* surface) const override final;

    inline void AddElement(std::unique_ptr<Element> element) {
        children_.push_back(std::move(element));
    }

private:
    std::vector<std::unique_ptr<Element>> children_;
};


#endif //XXX_LAYOUT_H
