//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_PICTURE_RECORDER_H
#define STRUGGLE_PICTURE_RECORDER_H

#include "render/painting/picture.h"

#include <third_party/skia/include/core/SkPictureRecorder.h>
class PictureRecorder {
public:
    SkCanvas* BeginRecording(SkRect bounds);

    std::unique_ptr<Picture> FinishRecording();

private:
    SkPictureRecorder picture_recorder_;
};


#endif //STRUGGLE_PICTURE_RECORDER_H
