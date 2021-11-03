//
// Created by guozhenxiong on 2021-11-03.
//

#include "performance_overlay_layer.h"

namespace sm {


PerformanceOverlayLayer::PerformanceOverlayLayer(Rect overlay_rect,
                                                 int options_mask,
                                                 int rasterizer_threshold,
                                                 bool checkerboard_raster_cache_images,
                                                 bool checkerboard_offscreen_layers)
  : overlay_rect_(overlay_rect),
    options_mask(options_mask),
    rasterizer_threshold(rasterizer_threshold),
    checkerboard_raster_cache_images(checkerboard_raster_cache_images),
    checkerboard_offscreen_layers(checkerboard_offscreen_layers)
{}

/// | Layer |
void PerformanceOverlayLayer::Paint(SkCanvas *canvas) const
{}

/// | Layer |
void PerformanceOverlayLayer::AddToScene(SceneBuilder *, Position)
{}

void PerformanceOverlayLayer::SetOverlayRect(Rect value)
{
    if (value != overlay_rect_) {
        overlay_rect_ = value;
        MarkNeedsAddToScene();
    }
}
} // namespace sm