//
// Created by guozhenxiong on 2021-10-08.
//

#ifndef STRUGGLE_RASTERIZER_H
#define STRUGGLE_RASTERIZER_H

#include <memory>

namespace strg {
class Scene;
class WindowContext;

class Rasterizer {
public:
    void Draw(std::unique_ptr<strg::Scene> scene);

    Rasterizer(WindowContext* window_context);
private:
    WindowContext* window_context_;
};
} // namespace strg

#endif //STRUGGLE_RASTERIZER_H
