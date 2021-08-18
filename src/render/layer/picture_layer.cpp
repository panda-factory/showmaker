//
// Created by guozhenxiong on 2021-08-18.
//

#include "picture_layer.h"

PictureLayer::PictureLayer(const SkPoint& offset, sk_sp<SkPicture> picture)
    : offset_(offset),
      picture_(std::move(picture))
{}

void PictureLayer::Paint(SkCanvas *canvas) const
{
    SkAutoCanvasRestore save(canvas, true);
    canvas->translate(offset_.x(), offset_.y());


    picture()->playback(canvas);
}