//
// Created by guozhenxiong on 2021-07-25.
//

#include "editor.h"
#include "shape.h"

namespace wtf {

namespace {
static inline SkRect Offset(SkRect r, SkIPoint p)
{
    return r.makeOffset((float) p.x(), (float) p.y());
}

size_t CountChar(const StringSlice& string, char value) {
    size_t count = 0;
    for (char c : string) { if (c == value) { ++count; } }
    return count;
}

template <typename F>
static void ReadLines(const void* data, size_t size, F f) {
    const char* start = (const char*)data;
    const char* end = start + size;
    const char* ptr = start;
    while (ptr < end) {
        while (*ptr++ != '\n' && ptr < end) {}
        size_t len = ptr - start;
        SkASSERT(len > 0);
        f(start, len);
        start = ptr;
    }
}

StringSlice RemoveNewline(const char* str, size_t len) {
    return SkASSERT((str != nullptr) || (len == 0)),
            StringSlice(str, (len > 0 && str[len - 1] == '\n') ? len - 1 : len);
}

inline const char* begin(const StringSlice& s) { return s.begin(); }

inline const char* end(const StringSlice& s) { return s.end(); }

inline bool IsUTF8Continuation(char v) {
    return ((unsigned char)v & 0b11000000) ==
           0b10000000;
}

const char* AlignUtf8(const char* p, const char* begin) {
    while (p > begin && IsUTF8Continuation(*p)) {
        --p;
    }
    return p;
}

size_t AlignColumn(const StringSlice& str, size_t p) {
    if (p >= str.size()) {
        return str.size();
    }
        return AlignUtf8(begin(str) + p, begin(str)) - begin(str);
}

const char* PrevUTF8(const char* p, const char* begin) {
    return p > begin ? AlignUtf8(p - 1, begin) : begin;
}

const char* NextUTF8(const char* p, const char* end) {
    if (p < end) {
        do {
            ++p;
        } while (p < end && IsUTF8Continuation(*p));
    }
    return p;
}

template <typename T>
size_t FindFirstLarger(const std::vector<T>& list, T value) {
    return (size_t)(std::upper_bound(list.begin(), list.end(), value) - list.begin());
}

size_t FindClosest_x(const std::vector<SkRect>& bounds, float x, size_t b, size_t e) {
    if (b >= e) {
        return b;
    }
    SkASSERT(e <= bounds.size());
    size_t best_index = b;
    float best_diff = ::fabsf(bounds[best_index].x() - x);
    for (size_t i = b + 1; i < e; ++i) {
        float d = ::fabsf(bounds[i].x() - x);
        if (d < best_diff) {
            best_diff = d;
            best_index = i;
        }
    }
    return best_index;
}
} // namespace


bool Editor::TextPosition::operator ==(const TextPosition& that) const
{
    return this->fParagraphIndex == that.fParagraphIndex && this->fTextByteIndex == that.fTextByteIndex;
}

bool Editor::TextPosition::operator!=(const TextPosition& that) const
{
    return !(*this == that);
}

bool Editor::TextPosition::operator<(const TextPosition& that) const
{
    return this->fParagraphIndex < that.fParagraphIndex ||
           (this->fParagraphIndex == that.fParagraphIndex && this->fTextByteIndex < that.fTextByteIndex);
}

SkRect Editor::GetLocation(TextPosition cursor)
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

void Editor::MarkDirty(TextLine* line) {
    line->blob_ = nullptr;
    line->shaped_ = false;
    line->word_boundaries_ = std::vector<bool>();
}

Editor::TextPosition Editor::Insert(TextPosition pos, const char* utf8Text, size_t byteLen) {

    pos = this->Move(Editor::Movement::kNowhere, pos);
    needs_reshape_ = true;
    if (pos.fParagraphIndex < lines_.size()) {
        lines_[pos.fParagraphIndex].text_.insert(pos.fTextByteIndex, utf8Text, byteLen);
        this->MarkDirty(&lines_[pos.fParagraphIndex]);
    } else {
        SkASSERT(pos.fParagraphIndex == lines_.size());
        SkASSERT(pos.fTextByteIndex == 0);
        lines_.push_back(Editor::TextLine(StringSlice(utf8Text, byteLen)));
    }
    pos = Editor::TextPosition{pos.fTextByteIndex + byteLen, pos.fParagraphIndex};
    size_t newlinecount = CountChar(lines_[pos.fParagraphIndex].text_, '\n');
    if (newlinecount > 0) {
        StringSlice src = std::move(lines_[pos.fParagraphIndex].text_);
        std::vector<TextLine>::const_iterator next = lines_.begin() + pos.fParagraphIndex + 1;
        lines_.insert(next, newlinecount, TextLine());
        TextLine* line = &lines_[pos.fParagraphIndex];
        ReadLines(src.begin(), src.size(), [&line](const char* str, size_t l) {
            (line++)->text_ = RemoveNewline(str, l);
        });
    }
    return pos;
}

Editor::TextPosition Editor::Move(Editor::Movement move, Editor::TextPosition pos) const {
    if (lines_.empty()) {
        return {0, 0};
    }
    // First thing: fix possible bad input values.
    if (pos.fParagraphIndex >= lines_.size()) {
        pos.fParagraphIndex = lines_.size() - 1;
        pos.fTextByteIndex = lines_[pos.fParagraphIndex].text_.size();
    } else {
        pos.fTextByteIndex = AlignColumn(lines_[pos.fParagraphIndex].text_, pos.fTextByteIndex);
    }

    SkASSERT(pos.fParagraphIndex < lines_.size());
    SkASSERT(pos.fTextByteIndex <= lines_[pos.fParagraphIndex].text_.size());

    SkASSERT(pos.fTextByteIndex == lines_[pos.fParagraphIndex].text_.size() ||
             !IsUTF8Continuation(lines_[pos.fParagraphIndex].text_.begin()[pos.fTextByteIndex]));

    switch (move) {
        case Editor::Movement::kNowhere:
            break;
        case Editor::Movement::kLeft:
            if (0 == pos.fTextByteIndex) {
                if (pos.fParagraphIndex > 0) {
                    --pos.fParagraphIndex;
                    pos.fTextByteIndex = lines_[pos.fParagraphIndex].text_.size();
                }
            } else {
                const auto& str = lines_[pos.fParagraphIndex].text_;
                pos.fTextByteIndex =
                        PrevUTF8(begin(str) + pos.fTextByteIndex, begin(str)) - begin(str);
            }
            break;
        case Editor::Movement::kRight:
            if (lines_[pos.fParagraphIndex].text_.size() == pos.fTextByteIndex) {
                if (pos.fParagraphIndex + 1 < lines_.size()) {
                    ++pos.fParagraphIndex;
                    pos.fTextByteIndex = 0;
                }
            } else {
                const auto& str = lines_[pos.fParagraphIndex].text_;
                pos.fTextByteIndex =
                        NextUTF8(begin(str) + pos.fTextByteIndex, end(str)) - begin(str);
            }
            break;
        case Editor::Movement::kHome:
        {
            const std::vector<size_t>& list = lines_[pos.fParagraphIndex].line_end_offsets_;
            size_t f = FindFirstLarger(list, pos.fTextByteIndex);
            pos.fTextByteIndex = f > 0 ? list[f - 1] : 0;
        }
            break;
        case Editor::Movement::kEnd:
        {
            const std::vector<size_t>& list = lines_[pos.fParagraphIndex].line_end_offsets_;
            size_t f = FindFirstLarger(list, pos.fTextByteIndex);
            if (f < list.size()) {
                pos.fTextByteIndex = list[f] > 0 ? list[f] - 1 : 0;
            } else {
                pos.fTextByteIndex = lines_[pos.fParagraphIndex].text_.size();
            }
        }
            break;
        case Editor::Movement::kUp:
        {
            SkASSERT(pos.fTextByteIndex < lines_[pos.fParagraphIndex].cursor_pos_.size());
            float x = lines_[pos.fParagraphIndex].cursor_pos_[pos.fTextByteIndex].left();
            const std::vector<size_t>& list = lines_[pos.fParagraphIndex].line_end_offsets_;
            size_t f = FindFirstLarger(list, pos.fTextByteIndex);
            // list[f] > value.  value > list[f-1]
            if (f > 0) {
                // not the first line in paragraph.
                pos.fTextByteIndex = FindClosest_x(lines_[pos.fParagraphIndex].cursor_pos_, x,
                                                    (f == 1) ? 0 : list[f - 2],
                                                    list[f - 1]);
            } else if (pos.fParagraphIndex > 0) {
                --pos.fParagraphIndex;
                const auto& newLine = lines_[pos.fParagraphIndex];
                size_t r = newLine.line_end_offsets_.size();
                if (r > 0) {
                    pos.fTextByteIndex = FindClosest_x(newLine.cursor_pos_, x,
                                                        newLine.line_end_offsets_[r - 1],
                                                        newLine.cursor_pos_.size());
                } else {
                    pos.fTextByteIndex = FindClosest_x(newLine.cursor_pos_, x, 0,
                                                        newLine.cursor_pos_.size());
                }
            }
            pos.fTextByteIndex =
                    AlignColumn(lines_[pos.fParagraphIndex].text_, pos.fTextByteIndex);
        }
            break;
        case Editor::Movement::kDown:
        {
            const std::vector<size_t>& list = lines_[pos.fParagraphIndex].line_end_offsets_;
            float x = lines_[pos.fParagraphIndex].cursor_pos_[pos.fTextByteIndex].left();

            size_t f = FindFirstLarger(list, pos.fTextByteIndex);
            if (f < list.size()) {
                const auto& bounds = lines_[pos.fParagraphIndex].cursor_pos_;
                pos.fTextByteIndex = FindClosest_x(bounds, x, list[f],
                                                    f + 1 < list.size() ? list[f + 1]
                                                                        : bounds.size());
            } else if (pos.fParagraphIndex + 1 < lines_.size()) {
                ++pos.fParagraphIndex;
                const auto& bounds = lines_[pos.fParagraphIndex].cursor_pos_;
                const std::vector<size_t>& l2 = lines_[pos.fParagraphIndex].line_end_offsets_;
                pos.fTextByteIndex = FindClosest_x(bounds, x, 0,
                                                    l2.size() > 0 ? l2[0] : bounds.size());
            } else {
                pos.fTextByteIndex = lines_[pos.fParagraphIndex].text_.size();
            }
            pos.fTextByteIndex =
                    AlignColumn(lines_[pos.fParagraphIndex].text_, pos.fTextByteIndex);
        }
            break;
        case Editor::Movement::kWordLeft:
        {
            if (pos.fTextByteIndex == 0) {
                pos = this->Move(Editor::Movement::kLeft, pos);
                break;
            }
            const std::vector<bool>& words = lines_[pos.fParagraphIndex].word_boundaries_;
            SkASSERT(words.size() == lines_[pos.fParagraphIndex].text_.size());
            do {
                --pos.fTextByteIndex;
            } while (pos.fTextByteIndex > 0 && !words[pos.fTextByteIndex]);
        }
            break;
        case Editor::Movement::kWordRight:
        {
            const StringSlice& text = lines_[pos.fParagraphIndex].text_;
            if (pos.fTextByteIndex == text.size()) {
                pos = this->Move(Editor::Movement::kRight, pos);
                break;
            }
            const std::vector<bool>& words = lines_[pos.fParagraphIndex].word_boundaries_;
            SkASSERT(words.size() == text.size());
            do {
                ++pos.fTextByteIndex;
            } while (pos.fTextByteIndex < text.size() && !words[pos.fTextByteIndex]);
        }
            break;

    }
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
    auto cmp = [](const TextPosition &u, const TextPosition &v) { return u < v; };

    for (TextPosition pos = std::min(options.fSelectionBegin, options.fSelectionEnd, cmp),
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
    if (needs_reshape_) {
        if (lines_.empty()) {
            lines_.push_back(TextLine());
        }
        float shape_width = (float)(width_);

        int i = 0;
        for (TextLine& line : lines_) {
            if (!line.shaped_) {
                ShapeResult result = Shape(line.text_.begin(), line.text_.size(),
                                           font_, locale_, shape_width);
                line.blob_           = std::move(result.blob);
                line.line_end_offsets_ = std::move(result.lineBreakOffsets);
                line.cursor_pos_      = std::move(result.glyphBounds);
                line.word_boundaries_ = std::move(result.wordBreaks);
                line.height_         = result.verticalAdvance;
                line.shaped_ = true;
            }
            ++i;
        }

        int y = 0;
        for (TextLine& line : lines_) {
            line.origin_ = {0, y};
            y += line.height_;
        }
        height_ = y;
        needs_reshape_ = false;
    }
}

void Editor::SetFont(SkFont font) {
    if (font != font_) {
        font_ = std::move(font);
        needs_reshape_ = true;
        for (auto& l : lines_) { this->MarkDirty(&l); }
    }
}
} // namespace wtf