//
// Created by guozhenxiong on 2021-08-20.
//

#include "render_pipeline.h"

#include "render/element.h"
#include "render/painting/picture_recorder.h"
#include "render/compositing/scene_builder.h"

void RenderPipeline::FlushLayout(Element* element)
{
    element->PerformLayout();
}

void RenderPipeline::FlushPaint(Element* element)
{
    SceneBuilder builder;
    PictureRecorder recorder;

    auto canvas = recorder.BeginRecording({500, 500});
    element->Draw(canvas);

    auto picture = recorder.FinishRecording();
}

std::unique_ptr<Scene> RenderPipeline::CompositeFrame(Element *element)
{
    SceneBuilder builder;

    element->layer()->AddToScene(&builder);

    auto scene = builder.Build();

    return scene;
}