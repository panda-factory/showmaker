//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef WTF_WINDOW_WIN32_H
#define WTF_WINDOW_WIN32_H

#include <windows.h>

#include "window.h"
#include "surface/angle_surface_manager.h"
namespace wtf {
class WindowWin32 : public Window {
public:

    bool Attach() override;

    void Show() override;

    WindowWin32();
private:
    friend Window;
    bool Init(HINSTANCE instance);

    HINSTANCE   hInstance_;

    HWND        hWnd_;

    std::unique_ptr<AngleSurfaceManager> surface_manager_;
};
} // namespace wtf

#endif //WTF_WINDOW_WIN32_H
