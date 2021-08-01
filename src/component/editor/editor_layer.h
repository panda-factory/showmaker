//
// Created by guozhenxiong on 2021-07-25.
//

#ifndef XXX_EDITOR_LAYER_H
#define XXX_EDITOR_LAYER_H

#include "layer.h"
#include "third-party/skia/include/core/SkSurface.h"
#include "third-party/skia/include/core/SkTime.h"
#include "include/core/SkFont.h"
#include "editor.h"

namespace wtf {

class EditorLayer : public wtf::Layer {
public:
    static constexpr float kFontSize = 18;
    static constexpr char* kTypefaces[3] = {"sans-serif", "serif", "monospace"};
    static constexpr SkFontStyle::Weight kFontWeight = SkFontStyle::kNormal_Weight;
    static constexpr SkFontStyle::Width  kFontWidth  = SkFontStyle::kNormal_Width;
    static constexpr SkFontStyle::Slant  kFontSlant  = SkFontStyle::kUpright_Slant;

    void SetFont();

    void loadFile(const char* path);

    void OnPaint(SkSurface* surface) override;

    void OnResize(int width, int height) override;

    bool OnChar(const std::string& utf8) override;

    void OnAttach(Window* w) override;

    bool scroll(int delta);

    void Invalid();

    inline bool& blink() {return blink_;}

private:
    bool Move(Editor::TextPosition pos, bool shift);

    bool MoveCursor(Editor::Movement m, bool shift = false);

    SkString fPath;
    Window* parent_ = nullptr;
    // TODO(halcanary): implement a cross-platform clipboard interface.
    std::vector<char> fClipboard;
    Editor::TextPosition text_pos_{0, 0};
    Editor::TextPosition mark_pos_;
    int pos_ = 0;  // window pixel position in file
    int width_ = 0;  // window width
    int height_ = 0;  // window height
    int margin_ = 10;
    size_t fTypefaceIndex = 0;
    float fFontSize = kFontSize;
    bool fShiftDown = false;
    bool blink_ = false;
    bool fMouseDown = false;
    Editor editor_;
};
} // namespace wtf

#endif //XXX_EDITOR_LAYER_H
