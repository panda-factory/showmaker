//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_PICTURE_LAYER_H
#define STRUGGLE_PICTURE_LAYER_H

#include "render/layer/layer.h"

namespace strg {
class Picture;

class PictureLayer : public Layer {
public:
    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *builder, Position offset) override;

    inline Picture *picture() const
    { return picture_.get(); }

    void ResetPicture(std::unique_ptr<Picture> picture);

    PictureLayer(const SkPoint &offset, std::unique_ptr<Picture> picture);

    ~PictureLayer();

private:
    SkPoint offset_;

    std::unique_ptr<Picture> picture_;
};
} // namespace strg

#endif //STRUGGLE_PICTURE_LAYER_H
