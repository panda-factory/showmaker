//
// Created by guozhenxiong on 2021-08-18.
//

#include "picture_layer.h"
#include "render/compositing/scene_builder.h"

namespace sm {

PictureLayer::PictureLayer(const Rect &canvas_bounds)
  : canvas_bounds_(canvas_bounds), offset_(0.0f, 0.0)
{}

PictureLayer::PictureLayer(const Offset &offset)
        : offset_(offset)
{}

PictureLayer::PictureLayer(const Offset &offset, std::unique_ptr<Picture> picture)
        : offset_(offset),
          picture_(std::move(picture))
{}

PictureLayer::~PictureLayer() noexcept
{}

void PictureLayer::Paint(SkCanvas *canvas) const
{
    SkAutoCanvasRestore save(canvas, true);
    canvas->translate(offset_.x, offset_.y);

    if (picture_ == nullptr) {
        return;
    }
    picture()->OnPaint(canvas);
}

void PictureLayer::AddToScene(SceneBuilder *builder, Position offset)
{
    builder->AddPicture(offset.x, offset.y, std::move(picture_));
}

void PictureLayer::ResetPicture(std::unique_ptr<Picture> picture)
{
    picture_.reset();
    picture_ = std::move(picture);
}

void PictureLayer::SetPicture(std::unique_ptr<Picture> picture)
{
    MarkNeedsAddToScene();
    if (picture_ != nullptr) {
        picture_->Dispose();
    }

    picture_ = std::move(picture);
}
} // namespace sm