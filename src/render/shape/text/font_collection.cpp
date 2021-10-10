//
// Created by guozhenxiong on 2021-09-29.
//

#include "font_collection.h"

#include <third_party/skia/include/core/SkFontMgr.h>
#include <third_party/skia/include/core/SkGraphics.h>
#include <third_party/skia/include/core/SkStream.h>
#include <third_party/skia/include/core/SkTypeface.h>

namespace strg {

FontCollection::FontCollection()
        : collection_(std::make_shared<txt::FontCollection>()) {
    dynamic_font_manager_ = sk_make_sp<txt::DynamicFontManager>();
    collection_->SetDynamicFontManager(dynamic_font_manager_);
}

FontCollection::~FontCollection() {
    collection_.reset();
    SkGraphics::PurgeFontCache();
}

std::shared_ptr<txt::FontCollection> FontCollection::GetFontCollection() const {
    return collection_;
}

void FontCollection::SetupDefaultFontManager() {
    collection_->SetupDefaultFontManager();
}

} // namespace strg