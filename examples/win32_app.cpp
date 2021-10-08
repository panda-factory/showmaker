//
// Created by guozhenxiong on 2021-07-21.
//

#include <memory>

#include "window.h"
#include "engine/engine.h"
#include "render/elements/label.h"
#include "render/elements/view.h"
#include "render/layout/column.h"
#include <windows.h>
namespace {

double fNextTime = -DBL_MAX;
std::unique_ptr<strg::Window> window;

void OnIdle()
{
}

int main_win32(int argc, char **argv, HINSTANCE hInstance, int show)
{
    bool idled = false;

    window.reset(strg::Window::CreateNativeWindow(hInstance));
    window->Attach();

    auto column = std::make_unique<strg::Column>();
    column->AddElement(std::make_unique<strg::Label>("HelloWorld!"));
    column->AddElement(std::make_unique<strg::Label>("Hello!"));
    column->AddElement(std::make_unique<strg::Label>("World!"));
    column->AddElement(std::make_unique<strg::Label>("guozhenxiong!"));

    auto view = std::make_unique<strg::View>();
    view->Adopt(column.get());
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

