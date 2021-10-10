//
// Created by guozhenxiong on 2021-10-09.
//

#ifndef STRUGGLE_PARAGRAPH_H
#define STRUGGLE_PARAGRAPH_H

#include <third_party/flutter/third_party/txt/src/txt/paragraph.h>

namespace strg {
class Paragraph {
public:
    static std::unique_ptr<Paragraph> Create(std::unique_ptr<txt::Paragraph> txt_paragraph);

    void Layout(double width);

    void Paint(SkCanvas* canvas, double x, double y);

private:
    explicit Paragraph(std::unique_ptr<txt::Paragraph> paragraph);

    std::unique_ptr<txt::Paragraph> paragraph_;
};
} // namespace strg

#endif //STRUGGLE_PARAGRAPH_H
