//
// Created by guozhenxiong on 2021-08-18.
//

#include "picture.h"

std::unique_ptr<Picture> Picture::Create(sk_sp<SkPicture> sk_picture)
{
    std::unique_ptr<Picture> picture;
    picture.reset(new Picture(std::move(sk_picture)));
    return std::move(picture);
}

Picture::Picture(sk_sp<SkPicture> picture)
    : picture_(std::move(picture))
{}

Picture::~Picture() = default;

void Picture::OnPaint(SkCanvas *canvas)
{
    picture()->playback(canvas);
}