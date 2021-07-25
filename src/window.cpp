//
// Created by guozhenxiong on 2021-07-21.
//

#include "window.h"

#include "include/core/SkSurface.h"

namespace wtf {

Window::Window() = default;

Window::~Window() = default;

void Window::OnPaint() {
    if (!window_context_) {
        return;
    }
    if (!is_active) {
        return;
    }
    sk_sp<SkSurface> backbuffer = window_context_->GetBackbufferSurface();
    if (backbuffer == nullptr) {
        printf("no backbuffer!?\n");
        // TODO: try recreating testcontext
        return;
    }

    // draw into the canvas of this surface
    this->VisitLayers([](Layer* layer) { layer->OnPrePaint(); });
    this->VisitLayers([=](Layer* layer) { layer->OnPaint(backbuffer.get()); });

    backbuffer->flushAndSubmit();

    window_context_->SwapBuffers();

}

void Window::PushLayer(Layer* layer) {
    layer->OnAttach(this);
    layers_.push_back(layer);
}

void Window::VisitLayers(std::function<void(Layer*)> visitor) {
    for (int i = 0; i < layers_.count(); ++i) {
        if (layers_[i]->active_) {
            visitor(layers_[i]);
        }
    }
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

} // namespace wtf