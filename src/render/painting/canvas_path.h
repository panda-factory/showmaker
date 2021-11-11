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

    friend bool operator!= (const CanvasPath& path1, const CanvasPath& path2);

    CanvasPath() = default;

private:
};

using Path = CanvasPath;
} // namespace sm

#endif //SHOWMAKER_CANVAS_PATH_H
