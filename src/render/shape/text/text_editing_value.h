//
// Created by guozhenxiong on 2021-10-26.
//

#ifndef SHOWMAKER_TEXT_EDITING_VALUE_H
#define SHOWMAKER_TEXT_EDITING_VALUE_H
#include <string>
namespace sm {
class TextEditingValue {
public:
    void AddText(const std::u16string& text);

    inline size_t& position() { return position_; }

    inline std::u16string& text() { return text_; }

    TextEditingValue();

    TextEditingValue(std::string text);

    TextEditingValue(std::u16string text);

private:
    std::u16string text_;
    size_t position_;
};
} // namespace sm

#endif //SHOWMAKER_TEXT_EDITING_VALUE_H
