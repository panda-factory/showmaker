//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef WTF_WINDOW_H
#define WTF_WINDOW_H

#include <vector>
#include "window/window_context.h"
#include "engine/engine.h"
#include "render/shape/text/text_input_client.h"

namespace sm {
class Element;

class Window : public Engine::Delegate {
public:
    enum BackendType {
#ifdef SK_GL
        kNativeGL_BackendType,
#endif
#if SK_ANGLE && defined(SK_BUILD_FOR_WIN)
        kANGLE_BackendType,
#endif
#ifdef SK_DAWN
        kDawn_BackendType,
#endif
#ifdef SK_VULKAN
        kVulkan_BackendType,
#endif
#ifdef SK_METAL
        kMetal_BackendType,
#endif
#ifdef SK_DIRECT3D
        kDirect3D_BackendType,
#endif
        kRaster_BackendType,

        kLast_BackendType = kRaster_BackendType
    };
    enum {
        kBackendTypeCount = kLast_BackendType + 1
    };

    using OnBeginFrame = std::function<void()>;

    static Window* CreateNativeWindow(void* platformData);

    static void RegisterOnChar(std::function<void (const std::u16string& utf16)> on_char) {
        on_char_handler = on_char;
    }

    /// | Engine::Delegate |
    void OnEngineBeginFrame(fml::TimePoint frame_target_time) override;

    virtual bool Attach(BackendType attach_type) = 0;

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
