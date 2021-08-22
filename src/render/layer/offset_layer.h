//
// Created by guozhenxiong on 2021-08-22.
//

#ifndef XXX_OFFSET_LAYER_H
#define XXX_OFFSET_LAYER_H


class OffsetLayer {
public:
    void Paint(SkCanvas* canvas) const override;

    void AddToScene(SceneBuilder *,Position2D) override;

    TransformLayer(const SkMatrix& transform);

private:

};


#endif //XXX_OFFSET_LAYER_H
