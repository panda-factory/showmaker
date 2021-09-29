//
// Created by guozhenxiong on 2021-08-18.
//

#ifndef STRUGGLE_PICTURE_H
#define STRUGGLE_PICTURE_H

#include <memory>

#include <third_party/skia/include/core/SkPicture.h>

class Picture {
public:
    static std::unique_ptr<Picture> Create(sk_sp<SkPicture> picture);

    void OnPaint(SkCanvas *canvas);

    inline sk_sp<SkPicture> picture() const { return picture_; }

    ~Picture();
private:
    Picture() = default;

    Picture(sk_sp<SkPicture> picture);

    sk_sp<SkPicture> picture_;
};


#endif //STRUGGLE_PICTURE_H
