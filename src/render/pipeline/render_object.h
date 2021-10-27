//
// Created by guozhenxiong on 2021-10-27.
//

#ifndef SHOWMAKER_RENDER_OBJECT_H
#define SHOWMAKER_RENDER_OBJECT_H

#include "render/painting/paint_context.h"

namespace sm {
class RenderObject {
public:
    virtual void Paint(const PaintContext* context, Position offset) {}

    void MarkNeedsPaint();

    void PaintWithContext(const PaintContext* context, Position offset);

    inline std::shared_ptr<ContainerLayer>& layer() { return layer_; }

    inline bool& needs_paint() { return needs_paint_; }

    RenderObject();
protected:
    std::shared_ptr<ContainerLayer> layer_;

private:
    bool needs_paint_;
};
} // namespace sm

#endif //SHOWMAKER_RENDER_OBJECT_H
