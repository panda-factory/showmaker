//
// Created by guozhenxiong on 2021-08-22.
//

#include "paint_context.h"
#include "render/pipeline/render_object.h"
#include "render/layer/offset_layer.h"

namespace sm {
/// | static |
void PaintContext::RepaintCompositedChild(RenderObject* child)
{
    auto& layer = child->layer();
    if (layer == nullptr) {
        child->layer() = std::make_shared<OffsetLayer>(0.0f, 0.0f);
    }
    auto paint_context = std::make_unique<PaintContext>(SkRect::MakeXYWH(0, 0, 10, 10), layer.get());
    child->PaintWithContext(paint_context.get(), {0, 0});
}

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

void PaintContext::AppendLayer(std::shared_ptr<ContainerLayer> layer) const
{
    container_->Add(layer);
}

SkCanvas *PaintContext::canvas()
{
    if (canvas_ == nullptr) {
        canvas_ = recorder_.BeginRecording(bounds_);
        auto layer = std::make_shared<PictureLayer>(Offset(0.0f, 0.0f), nullptr);
        picture_layer_ = layer.get();
        container_->Add(layer);
    }

    return canvas_;
}

void PaintContext::PaintChild(RenderObject* child, Position offset) const
{
    CompositeChild(child, offset);
}

void PaintContext::CompositeChild(RenderObject* child, Position offset) const
{
    RepaintCompositedChild(child);

    auto layer = child->layer();
    AppendLayer(layer);
}
} // namespace sm