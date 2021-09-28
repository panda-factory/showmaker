//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef WTF_WINDOW_H
#define WTF_WINDOW_H

#include <vector>
#include "window_context.h"
#include "layer.h"
#include "engine/engine.h"

class Element;
namespace wtf {

class Window : public Engine::Delegate{
public:
    static Window* CreateNativeWindow(void* platformData);

    /// | Engine::Delegate |
    void OnEngineBeginFrame(fml::TimePoint frame_target_time) override;

    virtual bool Attach() = 0;
    virtual void Show() = 0;

    void ScheduleFrame();

    void DispatchTask();

    void Invalid();

    void PushLayer(Layer* layer);

    bool SignalLayers(std::function<bool (Layer*)> visitor);

    void Detach();

    bool OnChar(const std::string& utf8);

    void OnPaint();

    int width() const;
    int height() const;

    virtual ~Window();

    std::unique_ptr<Element> element_;

protected:
    friend WindowContext;

    void VisitLayers(std::function<void(Layer*)> visitor);

    virtual void OnInvalid() = 0;

    Window();

    bool is_content_invalidated = false;  // use this to avoid duplicate invalidate events
    SkTDArray<Layer*> layers_;
    bool is_active = true;
    std::unique_ptr<WindowContext> window_context_;

private:
    void MarkInvalidProcessed();

    void VisitRootElement(std::function<void (Element*)> visitor);

    std::unique_ptr<Engine> engine_;
};
} // namespace wtf

#endif //WTF_WINDOW_H
