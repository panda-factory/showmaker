//
// Created by guozhenxiong on 2021-07-30.
//

#ifndef XXX_UTF8_H
#define XXX_UTF8_H

#include <string>

class UTF {
public:
    static bool UTF16ToUTF8(const std::u16string& utf16, std::string& outUtf8);

    static size_t CountUTF8(const char* utf8);

    static size_t CountUTF8String(const std::string& utf8);

    static const char* NextUTF8(const char* first, const char* end);

};


#endif //XXX_UTF8_H
