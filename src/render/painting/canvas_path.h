//
// Created by guozhenxiong on 2021-11-04.
//

#ifndef SHOWMAKER_CANVAS_PATH_H
#define SHOWMAKER_CANVAS_PATH_H

#include "graphics/rect.h"

namespace sm {

class CanvasPath {
public:
    void AddRect(const Rect& rect);

    CanvasPath() = default;

private:
};

using Path = CanvasPath;
} // namespace sm

#endif //SHOWMAKER_CANVAS_PATH_H
