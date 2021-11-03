//
// Created by guozhenxiong on 2021-08-22.
//

#ifndef SHOWMAKER_OFFSET_LAYER_H
#define SHOWMAKER_OFFSET_LAYER_H

#include "render/layer/container_layer.h"
#include "graphics/offset.h"
namespace sm {
class OffsetLayer : public ContainerLayer {
public:
    /// | Layer |
    void Paint(SkCanvas *canvas) const override;

    /// | Layer |
    void AddToScene(SceneBuilder *, Position) override;

    void SetOffset(const Offset& value);

    explicit OffsetLayer(Offset offset = Offset::ZERO) :
        offset_(offset) {}

    OffsetLayer(const float x, const float y) :
        offset_({x, y}) {}

private:
    Offset offset_;
};
} // namespace sm

#endif //SHOWMAKER_OFFSET_LAYER_H
