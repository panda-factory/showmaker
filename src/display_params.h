//
// Created by guozhenxiong on 2021-07-22.
//

#ifndef STRUGGLE_DISPLAY_PARAMS_H
#define STRUGGLE_DISPLAY_PARAMS_H

#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkSurfaceProps.h"
#include "third_party/skia/include/gpu/GrContextOptions.h"

namespace strg {
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
} // namespace strg

#endif //STRUGGLE_DISPLAY_PARAMS_H
