//
// Created by guozhenxiong on 2021-08-18.
//

#include "picture_layer.h"
#include "render/compositing/scene_builder.h"

PictureLayer::PictureLayer(const SkPoint& offset, std::unique_ptr<Picture> picture)
    : offset_(offset),
      picture_(std::move(picture))
{}

PictureLayer::~PictureLayer() noexcept
{}

void PictureLayer::Paint(SkCanvas *canvas) const
{
    SkAutoCanvasRestore save(canvas, true);
    canvas->translate(offset_.x(), offset_.y());

    picture()->OnPaint(canvas);
}

void PictureLayer::AddToScene(SceneBuilder* builder, Position2D offset)
{
    builder->AddPicture(offset.x, offset.y, std::move(picture_));
}

void PictureLayer::ResetPicture(std::unique_ptr<Picture> picture)
{
    picture_.reset();
    picture_ = std::move(picture);
}