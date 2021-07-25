//
// Created by guozhenxiong on 2021-07-21.
//

#include <memory>

#include "window.h"

#include <windows.h>
namespace {

int main_win32(int argc, char **argv, HINSTANCE hInstance, int show)
{
    std::unique_ptr<wtf::Window> window(wtf::Window::CreateNativeWindow(hInstance));

    window->Attach();

    window->Show();

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

