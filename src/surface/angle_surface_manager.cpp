//
// Created by guozhenxiong on 2021-07-21.
//

#include "angle_surface_manager.h"
namespace wtf {

// | static |
std::unique_ptr<AngleSurfaceManager> AngleSurfaceManager::Create() {
    std::unique_ptr<AngleSurfaceManager> manager;
    manager.reset(new AngleSurfaceManager());
    if (!manager->initialize_succeeded_) {
        return nullptr;
    }
    return std::move(manager);
}

AngleSurfaceManager::AngleSurfaceManager()
{}

AngleSurfaceManager::~AngleSurfaceManager()
{}

bool AngleSurfaceManager::CreateSurface(HWND* hWnd,
                                        EGLint width,
                                        EGLint height) {
    if (!hWnd || !initialize_succeeded_) {
        return false;
    }

    EGLSurface surface = EGL_NO_SURFACE;

    const EGLint surfaceAttributes[] = {
            EGL_FIXED_SIZE_ANGLE, EGL_TRUE, EGL_WIDTH, width,
            EGL_HEIGHT,           height,   EGL_NONE};

    surface = eglCreateWindowSurface(
            egl_display_, egl_config_,
            static_cast<EGLNativeWindowType>(*hWnd),
            surfaceAttributes);

    if (surface == EGL_NO_SURFACE) {
        //LogEglError("Surface creation failed.");
    }

    surface_width_ = width;
    surface_height_ = height;
    render_surface_ = surface;
    return true;
}

} // namespace wtf