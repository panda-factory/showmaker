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

void FontCollection::RegisterFonts(
        std::shared_ptr<AssetManager> asset_manager) {
    std::unique_ptr<fml::Mapping> manifest_mapping =
            asset_manager->GetAsMapping("FontManifest.json");
    if (manifest_mapping == nullptr) {
        FML_DLOG(WARNING) << "Could not find the font manifest in the asset store.";
        return;
    }

    rapidjson::Document document;
    static_assert(sizeof(decltype(document)::Ch) == sizeof(uint8_t), "");
    document.Parse(reinterpret_cast<const decltype(document)::Ch*>(
                           manifest_mapping->GetMapping()),
                   manifest_mapping->GetSize());

    if (document.HasParseError()) {
        FML_DLOG(WARNING) << "Error parsing the font manifest in the asset store.";
        return;
    }

    // Structure described in https://flutter.io/custom-fonts/

    if (!document.IsArray()) {
        return;
    }

    auto font_provider =
            std::make_unique<AssetManagerFontProvider>(asset_manager);

    for (const auto& family : document.GetArray()) {
        auto family_name = family.FindMember("family");
        if (family_name == family.MemberEnd() || !family_name->value.IsString()) {
            continue;
        }

        auto family_fonts = family.FindMember("fonts");
        if (family_fonts == family.MemberEnd() || !family_fonts->value.IsArray()) {
            continue;
        }

        for (const auto& family_font : family_fonts->value.GetArray()) {
            if (!family_font.IsObject()) {
                continue;
            }

            auto font_asset = family_font.FindMember("asset");
            if (font_asset == family_font.MemberEnd() ||
                !font_asset->value.IsString()) {
                continue;
            }

            // TODO(chinmaygarde): Handle weights and styles.
            font_provider->RegisterAsset(family_name->value.GetString(),
                                         font_asset->value.GetString());
        }
    }

    collection_->SetAssetFontManager(
            sk_make_sp<txt::AssetFontManager>(std::move(font_provider)));
}

void FontCollection::RegisterTestFonts() {
    std::vector<sk_sp<SkTypeface>> test_typefaces;
    std::vector<std::unique_ptr<SkStreamAsset>> font_data = GetTestFontData();
    for (auto& font : font_data) {
        test_typefaces.push_back(SkTypeface::MakeFromStream(std::move(font)));
    }

    std::unique_ptr<txt::TypefaceFontAssetProvider> font_provider =
            std::make_unique<txt::TypefaceFontAssetProvider>();

    size_t index = 0;
    std::vector<std::string> names = GetTestFontFamilyNames();
    for (sk_sp<SkTypeface> typeface : test_typefaces) {
        font_provider->RegisterTypeface(std::move(typeface), names[index]);
        index++;
    }

    collection_->SetTestFontManager(
            sk_make_sp<txt::TestFontManager>(std::move(font_provider), names));

    collection_->DisableFontFallback();
}

void FontCollection::LoadFontFromList(const uint8_t* font_data,
                                      int length,
                                      std::string family_name) {
    std::unique_ptr<SkStreamAsset> font_stream =
            std::make_unique<SkMemoryStream>(font_data, length, true);
    sk_sp<SkTypeface> typeface =
            SkTypeface::MakeFromStream(std::move(font_stream));
    txt::TypefaceFontAssetProvider& font_provider =
            dynamic_font_manager_->font_provider();
    if (family_name.empty()) {
        font_provider.RegisterTypeface(typeface);
    } else {
        font_provider.RegisterTypeface(typeface, family_name);
    }
    collection_->ClearFontFamilyCache();
}
} // namespace strg