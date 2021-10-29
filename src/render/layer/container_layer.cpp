//
// Created by guozhenxiong on 2021-08-18.
//

#include "container_layer.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {
void ContainerLayer::Add(std::shared_ptr<Layer> layer)
{
    layers_.emplace_back(std::move(layer));
}

void ContainerLayer::Append(Layer* child)
{
    AdoptChild(child);
    child->previous_sibling_ = last_child_;
    if (last_child_ != nullptr) {
        last_child_->next_sibling_ = child;
    }
    last_child_ = child;
    if (first_child_ == nullptr) {
        first_child_ = child;
    }

    FML_CHECK(child->Attached() == Attached());
}

void ContainerLayer::Paint(SkCanvas *canvas) const
{
    PaintChildren(canvas);
}

void ContainerLayer::PaintChildren(SkCanvas *canvas) const
{
    for (auto &layer : layers_) {
        layer->Paint(canvas);
    }
}

void ContainerLayer::AddToScene(SceneBuilder *builder, Position offset)
{
    AddChildrenToScene(builder, offset);
}

void ContainerLayer::AddChildrenToScene(SceneBuilder *builder, Position offset)
{
    for (auto &layer : layers_) {
        layer->AddToScene(builder);
    }
}

void ContainerLayer::RemoveChild(Layer* child)
{
    FML_CHECK(child->parent_ == this);
    FML_CHECK(child->Attached() == Attached());

    if (child->previous_sibling_ == nullptr) {
        FML_CHECK(first_child_ == child);
        first_child_ = child->next_sibling_;
    } else {
        if (child->previous_sibling_ != nullptr) {
            child->previous_sibling_->next_sibling_ = child->next_sibling_;
        }
    }
    if (child->next_sibling_ == nullptr) {
        FML_CHECK(last_child_ == child);
        last_child_ = child->previous_sibling_;
    } else {
        if (child->next_sibling_ != nullptr) {
            child->next_sibling_->previous_sibling_ = child->previous_sibling_;
        }
    }
    FML_CHECK((first_child_ == nullptr) == (last_child_ == nullptr));
    FML_CHECK(first_child_ == nullptr || first_child_->Attached() == Attached());
    FML_CHECK(last_child_ == nullptr || last_child_->Attached() == Attached());
    child->previous_sibling_ = nullptr;
    child->next_sibling_ = nullptr;
    DropChild(child);
    child->parent_ = nullptr;
    FML_CHECK(!child->Attached());
}

#if TESTING
std::list<Layer*> ContainerLayer::DepthFirstIterateChildren()
{
    if (first_child_ == nullptr)
        return std::list<Layer*>();
    std::list<Layer*> children;
    Layer* child = first_child_;
    while(child != nullptr) {
        children.emplace_back(child);
        if (auto ptr = dynamic_cast<ContainerLayer*>(child); ptr != nullptr) {
            children.splice(children.end(), ptr->DepthFirstIterateChildren());
        }
        child = child->next_sibling_;
    }
    return children;
}
void ContainerLayer::UpdateSubtreeNeedsAddToScene()
{
    Layer::UpdateSubtreeNeedsAddToScene();
    Layer* child = first_child_;
    while (child != nullptr) {
        child->UpdateSubtreeNeedsAddToScene();
        needs_add2scene_ = needs_add2scene_ || child->needs_add2scene_;
        child = child->next_sibling_;
    }
}
#endif // TESTING

} // namespace sm