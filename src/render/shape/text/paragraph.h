//
// Created by guozhenxiong on 2021-10-09.
//

#ifndef SHOWMAKER_PARAGRAPH_H
#define SHOWMAKER_PARAGRAPH_H

#include <third_party/flutter/third_party/txt/src/txt/paragraph.h>

namespace sm {

enum TextAffinity {
    UPSTREAM,
    DOWNSTREAM,
};
struct TextPosition {
    size_t offset;
    TextAffinity affinity;
};

class Paragraph {
public:
    static std::unique_ptr<Paragraph> Create(std::unique_ptr<txt::Paragraph> txt_paragraph);

    inline double width() { return paragraph_->GetMaxWidth(); }

    inline double height() { return paragraph_->GetHeight(); }

    std::vector<txt::Paragraph::TextBox> GetRectsForRange(unsigned start,
                                                          unsigned end);

    TextPosition GetPositionForOffset(double dx, double dy);

    void Layout(double width);

    void Paint(SkCanvas* canvas, double x, double y);

private:
    explicit Paragraph(std::unique_ptr<txt::Paragraph> paragraph);

    std::unique_ptr<txt::Paragraph> paragraph_;
};
} // namespace sm

#endif //SHOWMAKER_PARAGRAPH_H
