//
// Created by guozhenxiong on 2021-07-22.
//

#ifndef XXX_DISPLAY_PARAMS_H
#define XXX_DISPLAY_PARAMS_H

#include "third-party/skia/include/core/SkImageInfo.h"
#include "third-party/skia/include/core/SkSurfaceProps.h"
#include "third-party/skia/include/gpu/GrContextOptions.h"

namespace wtf {
struct DisplayParams {
    DisplayParams()
            : fColorType(kN32_SkColorType)
            , fColorSpace(nullptr)
            , fMSAASampleCount(1)
            , fSurfaceProps(0, kRGB_H_SkPixelGeometry)
            , fDisableVsync(false)
            , fDelayDrawableAcquisition(false)
            , fEnableBinaryArchive(false)
    {}

    SkColorType         fColorType;
    sk_sp<SkColorSpace> fColorSpace;
    int                 fMSAASampleCount;
    GrContextOptions    fGrContextOptions;
    SkSurfaceProps      fSurfaceProps;
    bool                fDisableVsync;
    bool                fDelayDrawableAcquisition;
    bool                fEnableBinaryArchive;
};
} // namespace wtf

#endif //XXX_DISPLAY_PARAMS_H
