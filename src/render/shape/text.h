//
// Created by guozhenxiong on 2021-08-05.
//

#ifndef XXX_TEXT_H
#define XXX_TEXT_H

#include "render/shape.h"

class Text : public Shape {
public:
    void Draw(SkCanvas*) const;

private:
    std::string text_;
};


#endif //XXX_TEXT_H
