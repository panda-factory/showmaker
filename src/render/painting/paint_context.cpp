//
// Created by guozhenxiong on 2021-08-22.
//

#include "paint_context.h"

namespace strg {
PaintContext::PaintContext(const SkRect &bounds, ContainerLayer *container)
        : canvas_(nullptr), bounds_(bounds), container_(container), picture_layer_(nullptr)
{
}

PaintContext::~PaintContext()
{
    if (canvas_ != nullptr) {
        auto picture = recorder_.FinishRecording();
        picture_layer_->ResetPicture(std::move(picture));
    }
}

SkCanvas *PaintContext::canvas()
{
    if (canvas_ == nullptr) {
        canvas_ = recorder_.BeginRecording(bounds_);
        auto layer = std::make_shared<PictureLayer>(SkPoint({0, 0}), nullptr);
        picture_layer_ = layer.get();
        container_->Add(layer);
    }

    return canvas_;
}
} // namespace strg