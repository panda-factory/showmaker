//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef XXX_PICTURE_H
#define XXX_PICTURE_H

#include <memory>

#include <third-party/skia/include/core/SkPicture.h>

class Picture {
public:
    static std::unique_ptr<Picture> Create(sk_sp<SkPicture> picture);

    inline sk_sp<SkPicture> picture() const { return picture_; }

    ~Picture();
private:
    Picture() = default;
    Picture(sk_sp<SkPicture> picture);

    sk_sp<SkPicture> picture_;
};


#endif //XXX_PICTURE_H
