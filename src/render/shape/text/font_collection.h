//
// Created by guozhenxiong on 2021-09-29.
//

#ifndef SHOWMAKER_FONT_COLLECTION_H
#define SHOWMAKER_FONT_COLLECTION_H

#include <memory>

#include <third_party/flutter/third_party/txt/src/txt/font_collection.h>

namespace sm {
class FontCollection {
public:
    std::shared_ptr<txt::FontCollection> GetFontCollection() const;

    void SetupDefaultFontManager();

    FontCollection();

    ~FontCollection();

private:
    std::shared_ptr<txt::FontCollection> collection_;
    sk_sp<txt::DynamicFontManager> dynamic_font_manager_;

    FML_DISALLOW_COPY_AND_ASSIGN(FontCollection);
};
} // namespace sm

#endif //SHOWMAKER_FONT_COLLECTION_H
