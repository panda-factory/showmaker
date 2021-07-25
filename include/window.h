//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef WTF_WINDOW_H
#define WTF_WINDOW_H

#include <memory>
#include "window_context.h"
#include "layer.h"

namespace wtf {


class Window {
public:
    static Window* CreateNativeWindow(void* platformData);

    virtual bool Attach() = 0;
    virtual void Show() = 0;

    void PushLayer(Layer* layer);

    void Detach();

    void OnPaint();

    int width() const;
    int height() const;

    virtual ~Window();

protected:
    friend WindowContext;

    void VisitLayers(std::function<void(Layer*)> visitor);

    Window();


    SkTDArray<Layer*> layers_;
    bool is_active = true;
    std::unique_ptr<WindowContext> window_context_;

};
} // namespace wtf

#endif //WTF_WINDOW_H
