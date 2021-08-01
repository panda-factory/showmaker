//
// Created by guozhenxiong on 2021-07-30.
//

#include "UTF8.h"
#include "ConvertUTF.h"

namespace {

template <typename T>
struct ConvertTrait {
    typedef T ArgType;
};
template <>
struct ConvertTrait<char> {
    typedef UTF8 ArgType;
};
template <>
struct ConvertTrait<char16_t> {
    typedef UTF16 ArgType;
};
template <>
struct ConvertTrait<char32_t> {
    typedef UTF32 ArgType;
};

template <typename From, typename To, typename FromTrait = ConvertTrait<From>, typename ToTrait = ConvertTrait<To>>
bool utfConvert(
        const std::basic_string<From>& from, std::basic_string<To>& to,
        ConversionResult(*cvtfunc)(const typename FromTrait::ArgType**, const typename FromTrait::ArgType*,
                                   typename ToTrait::ArgType**, typename ToTrait::ArgType*,
                                   ConversionFlags)
)
{
    static_assert(sizeof(From) == sizeof(typename FromTrait::ArgType), "Error size mismatched");
    static_assert(sizeof(To) == sizeof(typename ToTrait::ArgType), "Error size mismatched");

    if (from.empty())
    {
        to.clear();
        return true;
    }

    // See: http://unicode.org/faq/utf_bom.html#gen6
    static const int most_bytes_per_character = 4;

    const size_t maxNumberOfChars = from.length(); // all UTFs at most one element represents one character.
    const size_t numberOfOut = maxNumberOfChars * most_bytes_per_character / sizeof(To);

    std::basic_string<To> working(numberOfOut, 0);

    auto inbeg = reinterpret_cast<const typename FromTrait::ArgType*>(&from[0]);
    auto inend = inbeg + from.length();


    auto outbeg = reinterpret_cast<typename ToTrait::ArgType*>(&working[0]);
    auto outend = outbeg + working.length();
    auto r = cvtfunc(&inbeg, inend, &outbeg, outend, strictConversion);
    if (r != conversionOK)
        return false;

    working.resize(reinterpret_cast<To*>(outbeg) - &working[0]);
    to = std::move(working);

    return true;
}
} // namespace

bool UTF::UTF16ToUTF8(const std::u16string& utf16, std::string& out_utf8)
{
    return utfConvert(utf16, out_utf8, ConvertUTF16toUTF8);
}

size_t UTF::CountUTF8(const char* utf8)
{
    return getUTF8StringLength((const UTF8*)utf8);
}

size_t UTF::CountUTF8String(const std::string& utf8)
{
    return getUTF8StringLength((const UTF8*)utf8.c_str());
}

const char* UTF::NextUTF8(const char* ptr, const char* end)
{
    const UTF8* utf8 = (const UTF8*)ptr;
    return ptr + getNumBytesForUTF8(*utf8);
}