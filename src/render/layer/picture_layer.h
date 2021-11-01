//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_PICTURE_LAYER_H
#define SHOWMAKER_PICTURE_LAYER_H

#include "render/layer/layer.h"
#include "graphics/rect.h"
#include "graphics/offset.h"

namespace sm {
class Picture;

class PictureLayer : public Layer {
public:
    void Paint(SkCanvas *canvas) const override;

    void AddToScene(SceneBuilder *builder, Position offset) override;

    void SetPicture(std::unique_ptr<Picture> picture);

    inline Picture *picture() const
    { return picture_.get(); }

    void ResetPicture(std::unique_ptr<Picture> picture);

    PictureLayer(const Rect &canvas_bounds);

    PictureLayer(const Offset &offset);

    PictureLayer(const Offset &offset, std::unique_ptr<Picture> picture);

    ~PictureLayer();

private:
    Offset offset_;

    Rect canvas_bounds_;

    std::unique_ptr<Picture> picture_;
};
} // namespace sm

#endif //SHOWMAKER_PICTURE_LAYER_H
