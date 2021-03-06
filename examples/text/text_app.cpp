//
// Created by guozhenxiong on 2021-10-10.
//


#include <memory>

#include "window/window.h"
#include "engine/engine.h"
#include "render/elements/label.h"
#include "render/elements/view.h"
#include "render/layout/column.h"
#include "render/shape/text/paragraph_builder.h"
#include "render/compositing/scene.h"
#include "render/compositing/scene_builder.h"
#include <windows.h>

#include <third_party/ConvertUTF/UTF8.h>

namespace {
#ifdef SK_VULKAN
static constexpr sm::Window::BackendType kBackendType = sm::Window::kVulkan_BackendType;
#elif SK_METAL
static constexpr sm::Window::BackendType kBackendType = sm::Window::kMetal_BackendType;
#elif SK_GL
static constexpr sm::Window::BackendType kBackendType = sm::Window::kNativeGL_BackendType;
#elif SK_DAWN
static constexpr sm::Window::BackendType kBackendType = sm::Window::kDawn_BackendType;
#else
static constexpr sm::Window::BackendType kBackendType = sm::Window::kRaster_BackendType;
#endif
double fNextTime = -DBL_MAX;
std::unique_ptr<sm::Window> window;

std::unique_ptr<sm::Picture> Paint()
{
    sm::PictureRecorder recorder;

    auto canvas = recorder.BeginRecording({500, 500});

    auto builder = std::make_unique<sm::ParagraphBuilder>(12, 12);
    std::u16string out;
    UTF::UTF8ToUTF16("text for paragraph", out);
    //builder->PushTextStyle();
    builder->AddText(out);
    auto paragraph = builder->Build();
    paragraph->Layout(120);
    paragraph->Paint(canvas, 0, 0);

    return recorder.FinishRecording();
}

std::unique_ptr<sm::Scene> Composite(std::unique_ptr<sm::Picture> picture)
{
    sm::SceneBuilder builder;
    builder.PushOffset(0, 0);
    builder.AddPicture(0, 0, std::move(picture));
    builder.Pop();
    return builder.Build();
}

int main_win32(int argc, char **argv, HINSTANCE hInstance, int show)
{
    window.reset(sm::Window::CreateNativeWindow(hInstance));
    window->Attach(kBackendType);

    window->Show();

    window->RegisterOnBeginFrame(
            [window = window.get()] () {
                auto scene = Composite(Paint());
                window->Render(std::move(scene));
            });

    window->ScheduleFrame();
    return 0;
}

} // anonymous namespace

int main(int argc, char**argv) {
    main_win32(argc, argv, GetModuleHandle(NULL), SW_SHOW);

    MSG msg;
    memset(&msg, 0, sizeof(msg));

    // Main message loop
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);

            if (WM_PAINT == msg.message) {
            }
            DispatchMessage(&msg);
        } else {
        }
    }

    return (int)msg.wParam;
}

