//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef XXX_PICTURE_LAYER_H
#define XXX_PICTURE_LAYER_H

#include "render/layer/layer.h"

class PictureLayer : public Layer {
public:
    void Paint(SkCanvas* canvas) const override;

    inline SkPicture* picture() const { return picture_.get(); }

    PictureLayer(const SkPoint& offset, sk_sp<SkPicture> picture);

private:
    SkPoint offset_;

    sk_sp<SkPicture> picture_;
};


#endif //XXX_PICTURE_LAYER_H
