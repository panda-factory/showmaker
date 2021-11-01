//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef SHOWMAKER_PICTURE_RECORDER_H
#define SHOWMAKER_PICTURE_RECORDER_H

#include "render/painting/picture.h"

#include <third_party/skia/include/core/SkPictureRecorder.h>
namespace sm {

class Canvas;

class PictureRecorder {
public:
    SkCanvas *BeginRecording(SkRect bounds);

    std::unique_ptr<Picture> FinishRecording();

    void SetCanvas(Canvas* canvas) { canvas_ = canvas; }
private:
    Canvas* canvas_;

    SkPictureRecorder picture_recorder_;
};
} // namespace sm

#endif //SHOWMAKER_PICTURE_RECORDER_H
