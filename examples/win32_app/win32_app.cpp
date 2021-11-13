//
// Created by guozhenxiong on 2021-07-21.
//

#include <memory>

#include "window/window.h"
#include "engine/engine.h"
#include "render/elements/label.h"
#include "render/elements/view.h"
#include "render/layout/column.h"
#include <Windows.h>
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

void OnIdle()
{
}

int main_win32(int argc, char **argv, HINSTANCE hInstance, int show)
{
    bool idled = false;

    window.reset(sm::Window::CreateNativeWindow(hInstance));
    window->Attach(kBackendType);

    auto column = std::make_unique<sm::Column>();
    column->AddElement(std::make_unique<sm::Label>("HelloWorld!"));
    column->AddElement(std::make_unique<sm::Label>("Hello!"));
    column->AddElement(std::make_unique<sm::Label>("World!"));
    column->AddElement(std::make_unique<sm::Label>("guozhenxiong!"));

    auto view = std::make_unique<sm::View>();
    view->AdoptChild(column.get());
    view->AddElement(std::move(column));
    window->element_ = std::move(view);

    window->Show();

    window->RegisterOnBeginFrame(
            [window = window.get()] () {
                window->OnPaint();
    });

    window->ScheduleFrame();

    MSG msg;
    memset(&msg, 0, sizeof(msg));

    // Main message loop
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);

            if (WM_PAINT == msg.message) {
                if (!idled) {
                    OnIdle();
                }
                idled = false;
            }
            DispatchMessage(&msg);
        } else {
            OnIdle();
            idled = true;
        }
    }

    return (int)msg.wParam;
}

} // anonymous namespace

int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev,
                      _In_ wchar_t *command_line, _In_ int show_command)
{

    ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);


    ::CoUninitialize();
    return EXIT_SUCCESS;
}

int main(int argc, char**argv) {
    return main_win32(argc, argv, GetModuleHandle(NULL), SW_SHOW);
}

