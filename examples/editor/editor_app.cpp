//
// Created by guozhenxiong on 2021-10-25.
//

#include <memory>

#include "window/window.h"
#include "engine/engine.h"
#include "render/elements/editable_text.h"
#include "render/elements/view.h"
#include "render/layout/column.h"
#include <windows.h>
namespace {

double fNextTime = -DBL_MAX;
std::unique_ptr<sm::Window> window;

void OnIdle()
{
}

int main_win32(int argc, char **argv, HINSTANCE hInstance, int show)
{
    bool idled = false;

    window.reset(sm::Window::CreateNativeWindow(hInstance));
    window->Attach();

    auto edit = std::make_unique<sm::EditableText>("HelloWorld!");

    auto view = std::make_unique<sm::View>();
    view->AdoptChild(edit.get());
    view->AddElement(std::move(edit));
    window->element_ = std::move(view);

    window->Show();

    window->RegisterOnBeginFrame(
            [window = window.get()] () {
                window->OnPaint();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                window->ScheduleFrame();
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


