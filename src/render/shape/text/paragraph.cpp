//
// Created by guozhenxiong on 2021-10-09.
//

#include "paragraph.h"

#include <flutter/fml/memory/ref_counted.h>

namespace sm {

/// | static |
std::unique_ptr<Paragraph> Paragraph::Create(std::unique_ptr<txt::Paragraph> txt_paragraph)
{
    std::unique_ptr<Paragraph> paragraph;
    paragraph.reset(new Paragraph(std::move(txt_paragraph)));

    return std::move(paragraph);
}

Paragraph::Paragraph(std::unique_ptr<txt::Paragraph> paragraph)
        : paragraph_(std::move(paragraph))
        {}


std::vector<txt::Paragraph::TextBox> Paragraph::GetRectsForRange(unsigned start,
                                                                 unsigned end)
{
    return paragraph_->GetRectsForRange(start, end, txt::Paragraph::RectHeightStyle::kMax, txt::Paragraph::RectWidthStyle::kTight);
}

TextPosition Paragraph::GetPositionForOffset(double dx, double dy)
{
    auto pos =  paragraph_->GetGlyphPositionAtCoordinate(dx, dy);

    return {pos.position, static_cast<TextAffinity>(pos.affinity)};
}

void Paragraph::Layout(double width) {
    paragraph_->Layout(width);
}

void Paragraph::Paint(SkCanvas* canvas, double x, double y) {
    paragraph_->Paint(canvas, x, y);
}
} // namespace sm