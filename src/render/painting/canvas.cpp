//
// Created by guozhenxiong on 2021-11-01.
//

#include "canvas.h"

#include "picture_recorder.h"

namespace sm {
Canvas::Canvas(PictureRecorder* recorder, Rect cullRect)
  : recorder_(recorder)
{
    recorder_->SetCanvas(this);

    canvas_ = recorder_->BeginRecording({cullRect.left, cullRect.top, cullRect.right, cullRect.bottom});
}
} // namespace sm