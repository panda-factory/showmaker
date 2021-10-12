//
// Created by guozhenxiong on 2021-10-10.
//

#ifndef SHOWMAKER_TEXT_STYLE_H
#define SHOWMAKER_TEXT_STYLE_H

#include "css/color.h"

namespace sm {
class TextStyle {
public:
    explicit TextStyle(const css::Color& color);
private:
    css::Color color_;
};
} // namespace sm

#endif //SHOWMAKER_TEXT_STYLE_H
