//
// Created by guozhenxiong on 2021-07-25.
//

#include "editor_layer.h"

namespace wtf {

bool EditorLayer::TextPosition::operator ==(const TextPosition& that) const
{
    return this->fParagraphIndex == that.fParagraphIndex && this->fTextByteIndex == that.fTextByteIndex;
}

bool EditorLayer::TextPosition::operator!=(const TextPosition& that) const
{
    return !(*this == that);
}

bool EditorLayer::TextPosition::operator<(const TextPosition& that) const
{
    return this->fParagraphIndex < that.fParagraphIndex ||
           (this->fParagraphIndex == that.fParagraphIndex && this->fTextByteIndex < that.fTextByteIndex);
}

void EditorLayer::SetFont()
{
}


void EditorLayer::OnPaint(SkSurface *surface)
{
    SkCanvas* canvas = surface->getCanvas();
    SkAutoCanvasRestore acr(canvas, true);
    canvas->clipRect({0, 0, (float)width_, (float)height_});
    canvas->translate(margin_, (float)(margin_ - pos_));

    PaintOpts options;
    options.fCursor = fTextPos;
    options.fCursorColor = {1, 0, 0, fBlink ? 0.0f : 1.0f};
    options.fBackgroundColor = SkColor4f{0.8f, 0.8f, 0.8f, 1};
    options.fCursorColor = {1, 0, 0, fBlink ? 0.0f : 1.0f};
    if (fMarkPos != TextPosition()) {
        options.fSelectionBegin = fMarkPos;
        options.fSelectionEnd = fTextPos;
    }

    Paint(canvas, options);
}

void EditorLayer::OnResize(int width, int height)
{
    if (SkISize{width_, height_} != SkISize{width, height}) {
        height_ = height;
        if (width != width_) {
            width_ = width;
        }
        //this->inval();
    }
}

void EditorLayer::OnAttach(Window *w)
{}
} // namespace wtf