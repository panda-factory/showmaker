//
// Created by guozhenxiong on 2021-08-21.
//

#include "view.h"

#include "render/painting/picture_recorder.h"
#include "render/layer/picture_layer.h"
#include "render/layer/transform_layer.h"

void View::Draw(SkCanvas* canvasxxx)
{
    PictureRecorder recorder;
    auto canvas = recorder.BeginRecording({500, 500});
    canvas->clear(SK_ColorWHITE);

    SkMatrix sk_matrix = SkMatrix::Translate(0, 0);
    auto offset_layer = std::make_shared<TransformLayer>(sk_matrix);
    layer()->Add(offset_layer);

    for(std::size_t i = 0; i < children_.size(); ++i)
    {
        PaintChild(children_[i].get(), canvasxxx);
    }

    canvas->restore();

    auto picture = recorder.FinishRecording();
    auto picture_layer = std::make_shared<PictureLayer>(SkPoint{0, 0}, std::move(picture));

    offset_layer->Add(picture_layer);
}

void View::PerformLayout()
{
    children_[0]->PerformLayout();
}

Size2D View::MeasureSize()
{
    return {};
}