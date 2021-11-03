//
// Created by guozhenxiong on 2021-11-03.
//

#ifndef SHOWMAKER_PERFORMANCE_OVERLAY_LAYER_H
#define SHOWMAKER_PERFORMANCE_OVERLAY_LAYER_H

#include "render/layer/layer.h"
#include "graphics/rect.h"

namespace sm {
class PerformanceOverlayLayer : public Layer{
public:
    /// | Layer |
    void Paint(SkCanvas *canvas) const override;

    /// | Layer |
    void AddToScene(SceneBuilder *, Position) override;

    void SetOverlayRect(Rect value);

    inline Rect GetOverlayRect() { return overlay_rect_; }

    PerformanceOverlayLayer(Rect overlay_rect,
                            int options_mask,
                            int rasterizer_threshold,
                            bool checkerboard_raster_cache_images,
                            bool checkerboard_offscreen_layers);

    int options_mask;

    int rasterizer_threshold;

    bool checkerboard_raster_cache_images;

    bool checkerboard_offscreen_layers;

private:
    Rect overlay_rect_;
};
} // namespace sm

#endif //SHOWMAKER_PERFORMANCE_OVERLAY_LAYER_H
