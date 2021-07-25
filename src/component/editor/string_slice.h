//
// Created by guozhenxiong on 2021-07-25.
//

#ifndef XXX_STRING_SLICE_H
#define XXX_STRING_SLICE_H
#include "string_view.h"

#include <memory>
#include <cstddef>
namespace wtf {
class StringSlice {
public:
    StringSlice() = default;
    StringSlice(const char* s, std::size_t l) { this->insert(0, s, l); }
    StringSlice(StringSlice&&);
    StringSlice(const StringSlice& that) : StringSlice(that.begin(), that.size()) {}
    ~StringSlice() = default;
    StringSlice& operator=(StringSlice&&);
    StringSlice& operator=(const StringSlice&);

    // access:
    // Does not have a c_str method; is *not* NUL-terminated.
    const char* begin() const { return fPtr.get(); }
    const char* end() const { return fPtr ? fPtr.get() + fLength : nullptr; }
    std::size_t size() const { return fLength; }
    StringView view() const { return {fPtr.get(), fLength}; }

    // mutation:
    void insert(std::size_t offset, const char* text, std::size_t length);
    void remove(std::size_t offset, std::size_t length);

    // modify capacity only:
    void reserve(std::size_t size) { if (size > fCapacity) { this->realloc(size); } }
    void shrink() { this->realloc(fLength); }

private:
    struct FreeWrapper { void operator()(void*); };
    std::unique_ptr<char[], FreeWrapper> fPtr;
    std::size_t fLength = 0;
    std::size_t fCapacity = 0;
    void realloc(std::size_t);
};
} // namespace wtf


#endif //XXX_STRING_SLICE_H
