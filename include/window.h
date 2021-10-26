//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef WTF_WINDOW_H
#define WTF_WINDOW_H

#include <vector>
#include "window_context.h"
#include "engine/engine.h"
#include "render/shape/text/text_input_client.h"

namespace sm {
class Element;

class Window : public Engine::Delegate{
public:
    using OnBeginFrame = std::function<void()>;

    static Window* CreateNativeWindow(void* platformData);

    static void RegisterOnChar(std::function<void (const std::u16string& utf16)> on_char) {
        on_char_handler = on_char;
    }

    /// | Engine::Delegate |
    void OnEngineBeginFrame(fml::TimePoint frame_target_time) override;

    virtual bool Attach() = 0;

    virtual bool HitTest(double x, double y);

    virtual void Show() = 0;

    void ScheduleFrame();

    void DispatchTask();

    void Invalid();

    void Detach();

    bool OnChar(const std::u16string& utf16);

    void OnPaint();

    int width() const;

    int height() const;

    void RegisterOnBeginFrame(const OnBeginFrame& on_begin_frame);

    void Render(std::unique_ptr<Scene> scene);

    virtual ~Window();

    std::unique_ptr<Element> element_;

protected:
    friend WindowContext;

    virtual void OnInvalid() = 0;

    Window();

    bool is_content_invalidated = false;  // use this to avoid duplicate invalidate events

    bool is_active = true;

    std::unique_ptr<WindowContext> window_context_;

    std::unique_ptr<Engine> engine_;

private:
    void MarkInvalidProcessed();

    void VisitRootElement(std::function<void (Element*)> visitor);

    static std::function<void (const std::u16string& utf16)> on_char_handler;

    OnBeginFrame on_begin_frame_;
};
} // namespace sm

#endif //WTF_WINDOW_H
