//
// Created by guozhenxiong on 2021-10-08.
//

#ifndef SHOWMAKER_RASTERIZER_H
#define SHOWMAKER_RASTERIZER_H

#include <memory>

namespace sm {
class Scene;
class WindowContext;

class Rasterizer {
public:
    void Draw(std::unique_ptr<sm::Scene> scene);

    Rasterizer(WindowContext* window_context);
private:
    WindowContext* window_context_;
};
} // namespace sm

#endif //SHOWMAKER_RASTERIZER_H
