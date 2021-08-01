//
// Created by guozhenxiong on 2021-07-25.
//

#include "editor_layer.h"

#include "window.h"

namespace wtf {

void EditorLayer::SetFont()
{
    editor_.SetFont(SkFont(SkTypeface::MakeFromName(kTypefaces[fTypefaceIndex],
                                                    SkFontStyle(kFontWeight, kFontWidth, kFontSlant)), fFontSize));
}


void EditorLayer::OnPaint(SkSurface *surface)
{
    SkCanvas* canvas = surface->getCanvas();
    SkAutoCanvasRestore acr(canvas, true);
    canvas->clipRect({0, 0, (float)width_, (float)height_});
    canvas->translate(margin_, (float)(margin_ - pos_));

    Editor::PaintOpts options;
    options.fCursor = text_pos_;
    options.fCursorColor = {1, 0, 0, blink_ ? 0.0f : 1.0f};
    options.fBackgroundColor = SkColor4f{0.8f, 0.8f, 0.8f, 1};
    options.fCursorColor = {1, 0, 0, blink_ ? 0.0f : 1.0f};
    if (mark_pos_ != Editor::TextPosition()) {
        options.fSelectionBegin = mark_pos_;
        options.fSelectionEnd = text_pos_;
    }

    editor_.Paint(canvas, options);
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

bool EditorLayer::OnChar(const std::string& utf8)
{
    const char* ch = utf8.c_str();
    editor_.Insert(text_pos_, ch, 1);
    return this->MoveCursor(Editor::Movement::kRight);
}

void EditorLayer::Invalid()
{
    if (parent_) {
        parent_->Invalid();
    }
}

bool EditorLayer::Move(Editor::TextPosition pos, bool shift) {
    if (pos == text_pos_ || pos == Editor::TextPosition()) {
        if (!shift) {
            text_pos_ = Editor::TextPosition();
        }
        return false;
    }
    if (shift != fShiftDown) {
        text_pos_ = shift ? text_pos_ : Editor::TextPosition();
        fShiftDown = shift;
    }
    text_pos_ = pos;

    // scroll if needed.
    SkIRect cursor = editor_.GetLocation(text_pos_).roundOut();
    if (pos_ < cursor.bottom() - height_ + 2 * margin_) {
        pos_ = cursor.bottom() - height_ + 2 * margin_;
    } else if (cursor.top() < pos_) {
        pos_ = cursor.top();
    }
    this->Invalid();

    return true;
}

bool EditorLayer::MoveCursor(Editor::Movement m, bool shift) {
    return this->Move(editor_.Move(m, text_pos_), shift);
}

void EditorLayer::OnAttach(Window *w)
{
    parent_ = w;
}
} // namespace wtf