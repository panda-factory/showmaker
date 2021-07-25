//
// Created by guozhenxiong on 2021-07-25.
//

#ifndef XXX_EDITOR_H
#define XXX_EDITOR_H

#include "include/core/SkColor.h"
#include "include/core/SkFont.h"
#include "include/core/SkString.h"
#include "include/core/SkTextBlob.h"

#include "string_slice.h"
#include "editor_layer.h"

#include <climits>
namespace wtf {
class Editor : public EditorLayer {
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
        size_t fTextByteIndex = SIZE_MAX;   // index into UTF-8 representation of line.
        size_t fParagraphIndex = SIZE_MAX;  // logical line, based on hard newline characters.
    };

    // get/set current font (used for shaping and displaying text)
    const SkFont& font() const { return font_; }
    void SetFont(SkFont font);

    SkRect GetLocation(EditorLayer::TextPosition cursor);

    EditorLayer::TextPosition Move(Editor::Movement move, EditorLayer::TextPosition pos) const;

protected:
    void Paint(SkCanvas* c, PaintOpts options) override;

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
    std::vector<TextLine> lines_;
    int width_ = 0;
    int height_ = 0;
    SkFont font_;
    bool needs_reshape_ = false;
    const char* locale_ = "en";  // TODO: make this setable

    void MarkDirty(TextLine*);
    void ReshapeAll();
};
} // namespace wtf

#endif //XXX_EDITOR_H
