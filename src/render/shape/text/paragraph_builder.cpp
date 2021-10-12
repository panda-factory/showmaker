//
// Created by guozhenxiong on 2021-10-09.
//

#include "paragraph_builder.h"

#include "font_collection.h"

namespace sm {
namespace {

// TextStyle

const int tsLeadingDistributionIndex = 0;
const int tsColorIndex = 1;
const int tsTextDecorationIndex = 2;
const int tsTextDecorationColorIndex = 3;
const int tsTextDecorationStyleIndex = 4;
const int tsFontWeightIndex = 5;
const int tsFontStyleIndex = 6;
const int tsTextBaselineIndex = 7;
const int tsTextDecorationThicknessIndex = 8;
const int tsFontFamilyIndex = 9;
const int tsFontSizeIndex = 10;
const int tsLetterSpacingIndex = 11;
const int tsWordSpacingIndex = 12;
const int tsHeightIndex = 13;
const int tsLocaleIndex = 14;
const int tsBackgroundIndex = 15;
const int tsForegroundIndex = 16;
const int tsTextShadowsIndex = 17;
const int tsFontFeaturesIndex = 18;

const int tsLeadingDistributionMask = 1 << tsLeadingDistributionIndex;
const int tsColorMask = 1 << tsColorIndex;
const int tsTextDecorationMask = 1 << tsTextDecorationIndex;
const int tsTextDecorationColorMask = 1 << tsTextDecorationColorIndex;
const int tsTextDecorationStyleMask = 1 << tsTextDecorationStyleIndex;
const int tsTextDecorationThicknessMask = 1 << tsTextDecorationThicknessIndex;
const int tsFontWeightMask = 1 << tsFontWeightIndex;
const int tsFontStyleMask = 1 << tsFontStyleIndex;
const int tsTextBaselineMask = 1 << tsTextBaselineIndex;
const int tsFontFamilyMask = 1 << tsFontFamilyIndex;
const int tsFontSizeMask = 1 << tsFontSizeIndex;
const int tsLetterSpacingMask = 1 << tsLetterSpacingIndex;
const int tsWordSpacingMask = 1 << tsWordSpacingIndex;
const int tsHeightMask = 1 << tsHeightIndex;
const int tsLocaleMask = 1 << tsLocaleIndex;
const int tsBackgroundMask = 1 << tsBackgroundIndex;
const int tsForegroundMask = 1 << tsForegroundIndex;
const int tsTextShadowsMask = 1 << tsTextShadowsIndex;
const int tsFontFeaturesMask = 1 << tsFontFeaturesIndex;

// ParagraphStyle

const int psTextAlignIndex = 1;
const int psTextDirectionIndex = 2;
const int psFontWeightIndex = 3;
const int psFontStyleIndex = 4;
const int psMaxLinesIndex = 5;
const int psTextHeightBehaviorIndex = 6;
const int psFontFamilyIndex = 7;
const int psFontSizeIndex = 8;
const int psHeightIndex = 9;
const int psStrutStyleIndex = 10;
const int psEllipsisIndex = 11;
const int psLocaleIndex = 12;

const int psTextAlignMask = 1 << psTextAlignIndex;
const int psTextDirectionMask = 1 << psTextDirectionIndex;
const int psFontWeightMask = 1 << psFontWeightIndex;
const int psFontStyleMask = 1 << psFontStyleIndex;
const int psMaxLinesMask = 1 << psMaxLinesIndex;
const int psFontFamilyMask = 1 << psFontFamilyIndex;
const int psFontSizeMask = 1 << psFontSizeIndex;
const int psHeightMask = 1 << psHeightIndex;
const int psTextHeightBehaviorMask = 1 << psTextHeightBehaviorIndex;
const int psStrutStyleMask = 1 << psStrutStyleIndex;
const int psEllipsisMask = 1 << psEllipsisIndex;
const int psLocaleMask = 1 << psLocaleIndex;

// TextShadows decoding

constexpr uint32_t kColorDefault = 0xFF000000;
constexpr uint32_t kBytesPerShadow = 16;
constexpr uint32_t kShadowPropertiesCount = 4;
constexpr uint32_t kColorOffset = 0;
constexpr uint32_t kXOffset = 1;
constexpr uint32_t kYOffset = 2;
constexpr uint32_t kBlurOffset = 3;

// FontFeature decoding
constexpr uint32_t kBytesPerFontFeature = 8;
constexpr uint32_t kFontFeatureTagLength = 4;

// Strut decoding
const int sFontWeightIndex = 0;
const int sFontStyleIndex = 1;
const int sFontFamilyIndex = 2;
const int sLeadingDistributionIndex = 3;
const int sFontSizeIndex = 4;
const int sHeightIndex = 5;
const int sLeadingIndex = 6;
const int sForceStrutHeightIndex = 7;

const int sFontWeightMask = 1 << sFontWeightIndex;
const int sFontStyleMask = 1 << sFontStyleIndex;
const int sFontFamilyMask = 1 << sFontFamilyIndex;
const int sLeadingDistributionMask = 1 << sLeadingDistributionIndex;
const int sFontSizeMask = 1 << sFontSizeIndex;
const int sHeightMask = 1 << sHeightIndex;
const int sLeadingMask = 1 << sLeadingIndex;
const int sForceStrutHeightMask = 1 << sForceStrutHeightIndex;

}  // namespace

ParagraphBuilder::ParagraphBuilder(double fontSize, double height)
{
    txt::ParagraphStyle style;
    style.font_size = fontSize;
    style.height = height;

    FontCollection font_collection;
    font_collection.SetupDefaultFontManager();

#if FLUTTER_ENABLE_SKSHAPER
#if FLUTTER_ALWAYS_USE_SKSHAPER
    bool enable_skparagraph = true;
#else
    bool enable_skparagraph = UIDartState::Current()->enable_skparagraph();
#endif
    if (enable_skparagraph) {
      factory = txt::ParagraphBuilder::CreateSkiaBuilder;
    }
#endif  // FLUTTER_ENABLE_SKSHAPER

    paragraph_builder_ = txt::ParagraphBuilder::CreateTxtBuilder(style, font_collection.GetFontCollection());
}

ParagraphBuilder::~ParagraphBuilder() = default;

void ParagraphBuilder::AddText(const std::u16string &text)
{
    if (text.empty()) {
        return;
    }

    paragraph_builder_->AddText(text);
}

std::unique_ptr<Paragraph> ParagraphBuilder::Build()
{
    return Paragraph::Create(paragraph_builder_->Build());
}

void ParagraphBuilder::PushTextStyle(const TextStyle& text_style)
{
    txt::TextStyle style = paragraph_builder_->PeekStyle();
    style.color = kColorDefault;

    paragraph_builder_->PushStyle(style);
}

} // namespace sm