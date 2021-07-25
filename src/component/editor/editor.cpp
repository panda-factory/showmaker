//
// Created by guozhenxiong on 2021-07-25.
//

#include "editor.h"


namespace wtf {

namespace {
static inline SkRect Offset(SkRect r, SkIPoint p)
{
    return r.makeOffset((float) p.x(), (float) p.y());
}
}


SkRect Editor::GetLocation(EditorLayer::TextPosition cursor)
{
    this->ReshapeAll();
    cursor = this->Move(Editor::Movement::kNowhere, cursor);
    if (lines_.size() > 0) {
        const TextLine &cLine = lines_[cursor.fParagraphIndex];
        SkRect pos = {0, 0, 0, 0};
        if (cursor.fTextByteIndex < cLine.cursor_pos_.size()) {
            pos = cLine.cursor_pos_[cursor.fTextByteIndex];
        }
        pos.fRight = pos.fLeft + 1;
        pos.fLeft -= 1;
        return Offset(pos, cLine.origin_);
    }
    return SkRect{0, 0, 0, 0};
}

EditorLayer::TextPosition Editor::Move(Editor::Movement move, EditorLayer::TextPosition pos) const
{
    return pos;
}

void Editor::Paint(SkCanvas *c, PaintOpts options)
{
    this->ReshapeAll();
    if (!c) {
        return;
    }

    c->drawPaint(SkPaint(options.fBackgroundColor));

    SkPaint selection = SkPaint(options.fSelectionColor);
    auto cmp = [](const EditorLayer::TextPosition &u, const EditorLayer::TextPosition &v) { return u < v; };

    for (EditorLayer::TextPosition pos = std::min(options.fSelectionBegin, options.fSelectionEnd, cmp),
                 end = std::max(options.fSelectionBegin, options.fSelectionEnd, cmp);
         pos < end;
         pos = this->Move(Editor::Movement::kRight, pos)) {
        SkASSERT(pos.fParagraphIndex < lines_.size());
        const TextLine &l = lines_[pos.fParagraphIndex];
        c->drawRect(Offset(l.cursor_pos_[pos.fTextByteIndex], l.origin_), selection);
    }

    if (lines_.size() > 0) {
        c->drawRect(Editor::GetLocation(options.fCursor), SkPaint(options.fCursorColor));
    }

    SkPaint foreground = SkPaint(options.fForegroundColor);
    for (const TextLine &line : lines_) {
        if (line.blob_) {
            c->drawTextBlob(line.blob_.get(), line.origin_.x(), line.origin_.y(), foreground);
        }
    }
}

void Editor::ReshapeAll()
{
}
} // namespace wtf