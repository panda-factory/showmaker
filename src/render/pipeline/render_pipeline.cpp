//
// Created by guozhenxiong on 2021-08-20.
//

#include "render_pipeline.h"

#include "render/elements/element.h"
#include "render/painting/picture_recorder.h"
#include "render/compositing/scene_builder.h"

namespace sm {
void RenderPipeline::FlushLayout(Element *element)
{
    element->PerformLayout();
}

void RenderPipeline::FlushPaint(Element *element)
{
    SceneBuilder builder;
    PictureRecorder recorder;

    element->OnPaint();

}

std::unique_ptr<Scene> RenderPipeline::CompositeFrame(Element *element)
{
    SceneBuilder builder;

    element->layer()->AddToScene(&builder);

    return builder.Build();
}
} // namespace sm