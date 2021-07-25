//
// Created by guozhenxiong on 2021-07-25.
//

#ifndef XXX_EDITOR_LAYER_H
#define XXX_EDITOR_LAYER_H

#include "layer.h"
#include "third-party/skia/include/core/SkCanvas.h"
#include "third-party/skia/include/core/SkSurface.h"
#include "third-party/skia/include/core/SkTime.h"
#include "include/core/SkFont.h"

namespace wtf {

class EditorLayer : public wtf::Layer {
public:
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
    static constexpr float kFontSize = 18;
    static constexpr char* kTypefaces[3] = {"sans-serif", "serif", "monospace"};
    static constexpr SkFontStyle::Weight kFontWeight = SkFontStyle::kNormal_Weight;
    static constexpr SkFontStyle::Width  kFontWidth  = SkFontStyle::kNormal_Width;
    static constexpr SkFontStyle::Slant  kFontSlant  = SkFontStyle::kUpright_Slant;

    void SetFont();

    void loadFile(const char* path);

    void OnPaint(SkSurface* surface) override;

    void OnResize(int width, int height) override;

    void OnAttach(Window* w) override;

    bool scroll(int delta);

    void inval();

protected:
    virtual void Paint(SkCanvas* c, PaintOpts options) = 0;

private:
    SkString fPath;
    Window* parent_ = nullptr;
    // TODO(halcanary): implement a cross-platform clipboard interface.
    std::vector<char> fClipboard;
    TextPosition fTextPos{0, 0};
    TextPosition fMarkPos;
    int pos_ = 0;  // window pixel position in file
    int width_ = 0;  // window width
    int height_ = 0;  // window height
    int margin_ = 10;
    size_t fTypefaceIndex = 0;
    float fFontSize = kFontSize;
    bool fShiftDown = false;
    bool fBlink = false;
    bool fMouseDown = false;
};
} // namespace wtf

#endif //XXX_EDITOR_LAYER_H
