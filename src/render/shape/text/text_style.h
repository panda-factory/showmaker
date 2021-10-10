//
// Created by guozhenxiong on 2021-10-10.
//

#ifndef STRUGGLE_TEXT_STYLE_H
#define STRUGGLE_TEXT_STYLE_H

#include "css/color.h"

namespace strg {
class TextStyle {
public:
    explicit TextStyle(const css::Color& color);
private:
    css::Color color_;
};
} // namespace strg

#endif //STRUGGLE_TEXT_STYLE_H
