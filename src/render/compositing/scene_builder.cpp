//
// Created by guozhenxiong on 2021-08-18.
//

#include "scene_builder.h"

#include <memory>

#include "render/layer/picture_layer.h"
#include "render/layer/transform_layer.h"
#include "render/layer/offset_layer.h"

namespace sm {
std::unique_ptr<SceneBuilder> SceneBuilder::Create()
{
    std::unique_ptr<SceneBuilder> builder;
    builder.reset(new SceneBuilder());
    return std::move(builder);
}

SceneBuilder::SceneBuilder() = default;

SceneBuilder::~SceneBuilder() = default;

std::unique_ptr<Scene> SceneBuilder::Build()
{
    if (layer_stack_.empty()) {
        return nullptr;
    }
    return Scene::Create(layer_stack_[0]);
}

void SceneBuilder::AddPicture(double dx,
                              double dy,
                              std::unique_ptr<Picture> picture)
{
    auto layer = std::make_unique<PictureLayer>(SkPoint::Make(dx, dy), std::move(picture));
    AddLayer(std::move(layer));
}

void SceneBuilder::PushOffset(double dx, double dy)
{
    auto layer = std::make_shared<OffsetLayer>(dx, dy);
    PushLayer(layer);
}

void SceneBuilder::AddLayer(std::shared_ptr<Layer> layer)
{

    if (!layer_stack_.empty()) {
        layer_stack_.back()->Add(std::move(layer));
    }
}

void SceneBuilder::PushLayer(std::shared_ptr<ContainerLayer> layer)
{
    AddLayer(layer);
    layer_stack_.push_back(std::move(layer));
}

void SceneBuilder::Pop()
{
    PopLayer();
}

void SceneBuilder::PopLayer()
{
    if (layer_stack_.size() > 1) {
        layer_stack_.pop_back();
    }
}
} // namespace sm