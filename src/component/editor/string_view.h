//
// Created by guozhenxiong on 2021-07-25.
//

#ifndef XXX_STRING_VIEW_H
#define XXX_STRING_VIEW_H

#include <cstddef>

namespace wtf {
template <typename T>
struct Span {
    T* data;
    std::size_t size;
};

using StringView = Span<const char>;
} // namespace wtf
#endif //XXX_STRING_VIEW_H
