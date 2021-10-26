//
// Created by guozhenxiong on 2021-10-26.
//

#ifndef SHOWMAKER_TEXT_INPUT_CLIENT_H
#define SHOWMAKER_TEXT_INPUT_CLIENT_H

#include <string>

namespace sm {
class TextInputClient {
public:
    //virtual void UpdateEditingValue(TextEditingValue value) {};
    virtual void OnChar(const std::u16string& c) {};
};
} // namespace sm

#endif //SHOWMAKER_TEXT_INPUT_CLIENT_H
