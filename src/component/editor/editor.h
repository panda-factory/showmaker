//
// Created by guozhenxiong on 2021-07-25.
//

#ifndef XXX_EDITOR_H
#define XXX_EDITOR_H

#include "include/core/SkColor.h"
#include "include/core/SkFont.h"
#include "include/core/SkString.h"
#include "include/core/SkTextBlob.h"
#include "third-party/skia/include/core/SkCanvas.h"

#include "string_slice.h"

#include <climits>
namespace wtf {
class Editor {
public:
    enum class Movement {
        kNowhere,
        kLeft,
        kUp,
        kRight,
        kDown,
        kHome,
        kEnd,
        kWordLeft,
        kWordRight,
    };
    struct TextPosition {
        bool operator ==(const TextPosition& that) const;
        bool operator!=(const TextPosition& that) const;
        bool operator<(const TextPosition& that) const;

        size_t fTextByteIndex = SIZE_MAX;   // index into UTF-8 representation of line.
        size_t fParagraphIndex = SIZE_MAX;  // logical line, based on hard newline characters.
    };
    struct PaintOpts {

        SkColor4f fBackgroundColor = {1, 1, 1, 1};
        SkColor4f fForegroundColor = {0, 0, 0, 1};
        // TODO: maybe have multiple selections and cursors, each with separate colors.
        SkColor4f fSelectionColor = {0.729f, 0.827f, 0.988f, 1};
        SkColor4f fCursorColor = {1, 0, 0, 1};
        TextPosition fSelectionBegin;
        TextPosition fSelectionEnd;
        TextPosition fCursor;
    };

    // get/set current font (used for shaping and displaying text)
    const SkFont& font() const { return font_; }
    void SetFont(SkFont font);

    SkRect GetLocation(TextPosition cursor);

    TextPosition Insert(TextPosition, const char* utf8Text, size_t byteLen);

    TextPosition Move(Editor::Movement move, TextPosition pos) const;

    void Paint(SkCanvas* c, PaintOpts options);

private:

    // TODO: rename this to TextParagraph. fLines to fParas.
    struct TextLine {
        StringSlice text_;
        sk_sp<const SkTextBlob> blob_;
        std::vector<SkRect> cursor_pos_;
        std::vector<size_t> line_end_offsets_;
        std::vector<bool> word_boundaries_;
        SkIPoint origin_ = {0, 0};
        int height_ = 0;
        bool shaped_ = false;

        TextLine(StringSlice t) : text_(std::move(t)) {}
        TextLine() {}
    };

    void MarkDirty(TextLine*);
    void ReshapeAll();

    std::vector<TextLine> lines_;
    int width_ = 0;
    int height_ = 0;
    SkFont font_;
    bool needs_reshape_ = false;
    const char* locale_ = "en";  // TODO: make this setable
};
} // namespace wtf

#endif //XXX_EDITOR_H
