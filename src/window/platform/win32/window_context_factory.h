//
// Created by guozhenxiong on 2021-11-13.
//

#ifndef SHOWMAKER_WINDOW_CONTEXT_FACTORY_H
#define SHOWMAKER_WINDOW_CONTEXT_FACTORY_H
#include "wtf/all_static.h"

namespace sm {
class WindowContextFactory : public AllStatic {
public:
    std::unique_ptr<WindowContext> MakeVulkanForWin(HWND, const DisplayParams&);

    std::unique_ptr<WindowContext> MakeGLForWin(HWND, const DisplayParams&);

    std::unique_ptr<WindowContext> MakeANGLEForWin(HWND, const DisplayParams&);

#ifdef SK_DIRECT3D
    std::unique_ptr<WindowContext> MakeD3D12ForWin(HWND, const DisplayParams&);
#endif

#ifdef SK_DAWN
    std::unique_ptr<WindowContext> MakeDawnD3D12ForWin(HWND, const DisplayParams&);
#endif

    std::unique_ptr<WindowContext> MakeRasterForWin(HWND, const DisplayParams&);

};
} // namespace sm
#endif //SHOWMAKER_WINDOW_CONTEXT_FACTORY_H
