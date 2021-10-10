//
// Created by guozhenxiong on 2021-10-09.
//

#ifndef STRUGGLE_PARAGRAPH_BUILDER_H
#define STRUGGLE_PARAGRAPH_BUILDER_H

#include "paragraph.h"
#include "text_style.h"

#include <third_party/flutter/third_party/txt/src/txt/paragraph_builder.h>

namespace strg {
class ParagraphBuilder {
public:
    void AddText(const std::u16string& text);

    std::unique_ptr<Paragraph> Build();

    void PushTextStyle(const TextStyle& text_style);

    ParagraphBuilder(double fontSize, double height);

    ~ParagraphBuilder();

private:
    std::unique_ptr<txt::ParagraphBuilder> paragraph_builder_;
};
} // namespace strg

#endif //STRUGGLE_PARAGRAPH_BUILDER_H
