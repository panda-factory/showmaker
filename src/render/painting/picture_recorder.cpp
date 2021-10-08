//
// Created by guozhenxiong on 2021-08-18.
//

#include "picture_recorder.h"

namespace strg {
SkCanvas *PictureRecorder::BeginRecording(SkRect bounds)
{
    return picture_recorder_.beginRecording(bounds);
}

std::unique_ptr<Picture> PictureRecorder::FinishRecording()
{
    return Picture::Create(picture_recorder_.finishRecordingAsPicture());
}
} // namespace strg