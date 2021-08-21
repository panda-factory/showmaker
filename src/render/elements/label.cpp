//
// Created by guozhenxiong on 2021-08-04.
//

#include "label.h"

#include <memory>

#include "render/shape/rectangle.h"
#include "render/painting/picture_recorder.h"
#include "render/layer/picture_layer.h"
#include "render/layer/transform_layer.h"
#include "render/painting/picture.h"

#include <third-party/skia/include/core/SkGraphics.h>

Label::Label(const std::string& text)
    :text_(text)
{

}

void Label::Draw(SkCanvas* canvasxxx)
{
    PictureRecorder recorder;
    auto canvas = recorder.BeginRecording({500, 500});
    auto rect = std::make_unique<Rectangle>(text_.MeasureSize());

    Element::Draw(canvas, rect.get(), position_);
    Element::Draw(canvas, &text_, position_);

    canvas->restore();

    auto picture = recorder.FinishRecording();
    auto picture_layer = std::make_shared<PictureLayer>(SkPoint{0, 0}, std::move(picture));

    SkMatrix sk_matrix = SkMatrix::Translate(0, 0);
    auto offset_layer = std::make_shared<TransformLayer>(sk_matrix);
    offset_layer->Add(picture_layer);
    layer()->Add(offset_layer);
}

Size2D Label::MeasureSize()
{
    const auto text_size = text_.MeasureSize();
    return text_size;
}