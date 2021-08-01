//
// Created by guozhenxiong on 2021-08-01.
//

#ifndef XXX_WORD_BOUNDARIES_H
#define XXX_WORD_BOUNDARIES_H

#include <cstddef>
#include <vector>

std::vector<bool> GetUtf8WordBoundaries(const char* begin, std::size_t byteLen, const char* locale);


#endif //XXX_WORD_BOUNDARIES_H
