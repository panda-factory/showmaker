//
// Created by guozhenxiong on 2021-10-26.
//

#include "text_editing_value.h"
#include <third_party/ConvertUTF/UTF8.h>

namespace sm {

TextEditingValue::TextEditingValue() = default;

TextEditingValue::TextEditingValue(std::string text)
{
    std::u16string out;
    UTF::UTF8ToUTF16(text, out);

    text_ = std::move(out);
    position_ = text_.size();
}

TextEditingValue::TextEditingValue(std::u16string text)
  : text_(text), position_(text_.size())
{}

void TextEditingValue::AddText(const std::u16string& text) {
    size_t position = position_;
    text_.insert(position, text);
    position_ = position + text.length();
}
} // namespace sm