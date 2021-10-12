//
// Created by guozhenxiong on 2021-07-21.
//

#include "window.h"

#include "render/elements/element.h"
#include "render/compositing/scene_builder.h"
#include "render/painting/picture_recorder.h"
#include "render/pipeline/render_pipeline.h"
#include "engine/rasterizer/rasterizer.h"

#include <include/core/SkSurface.h>

namespace sm {

//auto ui_runner = TaskRunner::Create("ui.thread");

Window::Window()
{
    engine_ = Engine::Create(*this);
}

Window::~Window()
{ }

/// | Engine::Delegate |
void Window::OnEngineBeginFrame(fml::TimePoint frame_target_time)
{
    if (on_begin_frame_) {
        on_begin_frame_();
    }
}

void Window::ScheduleFrame()
{
    engine_->ScheduleFrame();
}

void Window::DispatchTask()
{}

void Window::Invalid() {
    if (!window_context_) {
        return;
    }
    if (!is_content_invalidated) {
        is_content_invalidated = true;
        OnInvalid();
    }
}

void Window::MarkInvalidProcessed() {
    is_content_invalidated = false;
}

void Window::OnPaint() {
    if (!window_context_) {
        return;
    }
    window_context_->MakeCurrent();
    if (!is_active) {
        return;
    }

    MarkInvalidProcessed();

    // draw into the canvas of this surface
#if 0
    //this->VisitLayers([](Layer* layer) { layer->OnPrePaint(); });
    //this->VisitLayers([=](Layer* layer) { layer->OnPaint(backbuffer.get()); });
    SceneBuilder builder;
    PictureRecorder recorder;

    auto canvas = recorder.BeginRecording({500, 500});
    this->VisitRootElement([=](Element* element) {
        element->Draw(canvas);
    });
    auto picture = recorder.FinishRecording();

    builder.PushOffset(0.0f, 0.0f);
    builder.AddPicture(0.0f, 0.0f, std::move(picture));
    builder.Pop();

    auto scene = builder.Build();
#endif
    RenderPipeline::FlushLayout(element_.get());
    RenderPipeline::FlushPaint(element_.get());

    engine_->Render(RenderPipeline::CompositeFrame(element_.get()));

}

void Window::RegisterOnBeginFrame(const OnBeginFrame& on_begin_frame)
{
    on_begin_frame_ = std::move(on_begin_frame);
}

void Window::Render(std::unique_ptr<Scene> scene)
{
    engine_->Render(std::move(scene));
}

int Window::width() const {
    if (!window_context_) {
        return 0;
    }
    return window_context_->width();
}

int Window::height() const {
    if (!window_context_) {
        return 0;
    }
    return window_context_->height();
}

} // namespace sm