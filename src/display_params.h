//
// Created by guozhenxiong on 2021-07-22.
//

#ifndef SHOWMAKER_DISPLAY_PARAMS_H
#define SHOWMAKER_DISPLAY_PARAMS_H

#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkSurfaceProps.h"
#include "third_party/skia/include/gpu/GrContextOptions.h"

namespace sm {
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
} // namespace sm

#endif //SHOWMAKER_DISPLAY_PARAMS_H
