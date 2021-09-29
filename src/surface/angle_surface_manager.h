//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef STRUGGLE_ANGLE_SURFACE_MANAGER_H
#define STRUGGLE_ANGLE_SURFACE_MANAGER_H

// OpenGL ES and EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <memory>
#include <windows.h>

namespace strg {
class WindowWin32;
// A manager for inializing ANGLE correctly and using it to create and
// destroy surfaces
class AngleSurfaceManager {
public:
    static std::unique_ptr<AngleSurfaceManager> Create();
    ~AngleSurfaceManager();

    // Disallow copy/move.
    AngleSurfaceManager(const AngleSurfaceManager&) = delete;
    AngleSurfaceManager& operator=(const AngleSurfaceManager&) = delete;

    bool CreateSurface(HWND* hWnd,
                       EGLint width,
                       EGLint height);

    EGLBoolean SwapBuffers();

private:
    bool Initialize();
    void CleanUp();

private:
    friend WindowWin32;
    // Creates a new surface manager retaining reference to the passed-in target
    // for the lifetime of the manager.
    AngleSurfaceManager();

    // Attempts to initialize EGL using ANGLE.
    bool InitializeEGL(
            PFNEGLGETPLATFORMDISPLAYEXTPROC egl_get_platform_display_EXT,
            const EGLint* config,
            bool should_log);

    // EGL representation of native display.
    EGLDisplay egl_display_;

    // EGL representation of current rendering context.
    EGLContext egl_context_;

    // EGL representation of current rendering context used for async texture
    // uploads.
    EGLContext egl_resource_context_;

    // current frame buffer configuration.
    EGLConfig egl_config_;

    // State representing success or failure of display initialization used when
    // creating surfaces.
    bool initialize_succeeded_;

    // Current render_surface that engine will draw into.
    EGLSurface render_surface_ = EGL_NO_SURFACE;

    // Requested dimensions for current surface
    EGLint surface_width_ = 0;
    EGLint surface_height_ = 0;

    // Number of active instances of AngleSurfaceManager
    static int instance_count_;
};

}  // namespace strg


#endif //STRUGGLE_ANGLE_SURFACE_MANAGER_H
