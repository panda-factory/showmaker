//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef WTF_WINDOW_WIN32_H
#define WTF_WINDOW_WIN32_H

#include "window.h"

#include <windows.h>

namespace wtf {
class WindowWin32 : public Window {
public:

    bool Attach() override;

    void Show() override;

    WindowWin32();

protected:
    void OnInvalid() override;

private:
    friend Window;
    bool Init(HINSTANCE instance);

    HINSTANCE   hInstance_;
    HWND        hWnd_;

};
} // namespace wtf

#endif //WTF_WINDOW_WIN32_H
