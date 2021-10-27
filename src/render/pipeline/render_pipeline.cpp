//
// Created by guozhenxiong on 2021-08-20.
//

#include "render_pipeline.h"

#include "render/elements/element.h"
#include "render/painting/picture_recorder.h"
#include "render/compositing/scene_builder.h"

namespace sm {
std::list<RenderObject*> RenderPipeline::nodes_needing_paint_;

void RenderPipeline::AddNodeNeedingPaint(RenderObject* node)
{
    nodes_needing_paint_.emplace_back(node);
}

void RenderPipeline::FlushLayout(Element *element)
{
    element->PerformLayout();
}

void RenderPipeline::FlushPaint(Element *element)
{
    auto dirty_nodes = std::move(nodes_needing_paint_);
    for (auto node : dirty_nodes) {
        if (node->needs_paint() == true) {
            PaintContext::RepaintCompositedChild(node);
        }
    }

}

std::unique_ptr<Scene> RenderPipeline::CompositeFrame(Element *element)
{
    SceneBuilder builder;

    element->layer()->AddToScene(&builder);

    return builder.Build();
}
} // namespace sm