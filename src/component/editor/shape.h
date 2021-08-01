//
// Created by guozhenxiong on 2021-07-31.
//

#ifndef XXX_SHAPE_H
#define XXX_SHAPE_H

#include "include/core/SkFont.h"
#include "include/core/SkTextBlob.h"

#include <cstddef>
#include <vector>

struct ShapeResult {
    sk_sp<SkTextBlob> blob;
    std::vector<std::size_t> lineBreakOffsets;
    std::vector<SkRect> glyphBounds;
    std::vector<bool> wordBreaks;
    int verticalAdvance;
};

ShapeResult Shape(const char* ut8text,
                  size_t textByteLen,
                  const SkFont& font,
                  const char* locale,
                  float width);


#endif //XXX_SHAPE_H
