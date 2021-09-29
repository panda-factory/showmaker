
SET(TARGET_NAME lib_txt)
SET(TXT_SRC_DIR .)
SET(TXT_SRC
    ${TXT_SRC_DIR}/src/log/log.cc
    ${TXT_SRC_DIR}/src/log/log.h
    ${TXT_SRC_DIR}/src/minikin/CmapCoverage.cpp
    ${TXT_SRC_DIR}/src/minikin/CmapCoverage.h
    ${TXT_SRC_DIR}/src/minikin/Emoji.cpp
    ${TXT_SRC_DIR}/src/minikin/Emoji.h
    ${TXT_SRC_DIR}/src/minikin/FontCollection.cpp
    ${TXT_SRC_DIR}/src/minikin/FontCollection.h
    ${TXT_SRC_DIR}/src/minikin/FontFamily.cpp
    ${TXT_SRC_DIR}/src/minikin/FontFamily.h
    ${TXT_SRC_DIR}/src/minikin/FontLanguage.cpp
    ${TXT_SRC_DIR}/src/minikin/FontLanguage.h
    ${TXT_SRC_DIR}/src/minikin/FontLanguageListCache.cpp
    ${TXT_SRC_DIR}/src/minikin/FontLanguageListCache.h
    ${TXT_SRC_DIR}/src/minikin/FontUtils.cpp
    ${TXT_SRC_DIR}/src/minikin/FontUtils.h
    ${TXT_SRC_DIR}/src/minikin/GraphemeBreak.cpp
    ${TXT_SRC_DIR}/src/minikin/GraphemeBreak.h
    ${TXT_SRC_DIR}/src/minikin/HbFontCache.cpp
    ${TXT_SRC_DIR}/src/minikin/HbFontCache.h
    ${TXT_SRC_DIR}/src/minikin/Hyphenator.cpp
    ${TXT_SRC_DIR}/src/minikin/Hyphenator.h
    ${TXT_SRC_DIR}/src/minikin/Layout.cpp
    ${TXT_SRC_DIR}/src/minikin/Layout.h
    ${TXT_SRC_DIR}/src/minikin/LayoutUtils.cpp
    ${TXT_SRC_DIR}/src/minikin/LayoutUtils.h
    ${TXT_SRC_DIR}/src/minikin/LineBreaker.cpp
    ${TXT_SRC_DIR}/src/minikin/LineBreaker.h
    ${TXT_SRC_DIR}/src/minikin/Measurement.cpp
    ${TXT_SRC_DIR}/src/minikin/Measurement.h
    ${TXT_SRC_DIR}/src/minikin/MinikinFont.cpp
    ${TXT_SRC_DIR}/src/minikin/MinikinFont.h
    ${TXT_SRC_DIR}/src/minikin/MinikinInternal.cpp
    ${TXT_SRC_DIR}/src/minikin/MinikinInternal.h
    ${TXT_SRC_DIR}/src/minikin/SparseBitSet.cpp
    ${TXT_SRC_DIR}/src/minikin/SparseBitSet.h
    ${TXT_SRC_DIR}/src/minikin/WordBreaker.cpp
    ${TXT_SRC_DIR}/src/minikin/WordBreaker.h
    ${TXT_SRC_DIR}/src/txt/asset_font_manager.cc
    ${TXT_SRC_DIR}/src/txt/asset_font_manager.h
    ${TXT_SRC_DIR}/src/txt/font_asset_provider.cc
    ${TXT_SRC_DIR}/src/txt/font_asset_provider.h
    ${TXT_SRC_DIR}/src/txt/font_collection.cc
    ${TXT_SRC_DIR}/src/txt/font_collection.h
    ${TXT_SRC_DIR}/src/txt/font_features.cc
    ${TXT_SRC_DIR}/src/txt/font_features.h
    ${TXT_SRC_DIR}/src/txt/font_skia.cc
    ${TXT_SRC_DIR}/src/txt/font_skia.h
    ${TXT_SRC_DIR}/src/txt/font_style.h
    ${TXT_SRC_DIR}/src/txt/font_weight.h
    ${TXT_SRC_DIR}/src/txt/line_metrics.h
    ${TXT_SRC_DIR}/src/txt/paint_record.cc
    ${TXT_SRC_DIR}/src/txt/paint_record.h
    ${TXT_SRC_DIR}/src/txt/paragraph.h
    ${TXT_SRC_DIR}/src/txt/paragraph_builder.cc
    ${TXT_SRC_DIR}/src/txt/paragraph_builder.h
    ${TXT_SRC_DIR}/src/txt/paragraph_builder_txt.cc
    ${TXT_SRC_DIR}/src/txt/paragraph_builder_txt.h
    ${TXT_SRC_DIR}/src/txt/paragraph_style.cc
    ${TXT_SRC_DIR}/src/txt/paragraph_style.h
    ${TXT_SRC_DIR}/src/txt/paragraph_txt.cc
    ${TXT_SRC_DIR}/src/txt/paragraph_txt.h
    ${TXT_SRC_DIR}/src/txt/placeholder_run.cc
    ${TXT_SRC_DIR}/src/txt/placeholder_run.h
    ${TXT_SRC_DIR}/src/txt/platform.h
    ${TXT_SRC_DIR}/src/txt/run_metrics.h
    ${TXT_SRC_DIR}/src/txt/styled_runs.cc
    ${TXT_SRC_DIR}/src/txt/styled_runs.h
    #${TXT_SRC_DIR}/src/txt/test_font_manager.cc
    #${TXT_SRC_DIR}/src/txt/test_font_manager.h
    ${TXT_SRC_DIR}/src/txt/text_baseline.h
    ${TXT_SRC_DIR}/src/txt/text_decoration.cc
    ${TXT_SRC_DIR}/src/txt/text_decoration.h
    ${TXT_SRC_DIR}/src/txt/text_shadow.cc
    ${TXT_SRC_DIR}/src/txt/text_shadow.h
    ${TXT_SRC_DIR}/src/txt/text_style.cc
    ${TXT_SRC_DIR}/src/txt/text_style.h
    ${TXT_SRC_DIR}/src/txt/typeface_font_asset_provider.cc
    ${TXT_SRC_DIR}/src/txt/typeface_font_asset_provider.h
    ${TXT_SRC_DIR}/src/utils/JenkinsHash.cpp
    ${TXT_SRC_DIR}/src/utils/JenkinsHash.h
    ${TXT_SRC_DIR}/src/utils/LinuxUtils.h
    ${TXT_SRC_DIR}/src/utils/LruCache.h
    ${TXT_SRC_DIR}/src/utils/MacUtils.h
    ${TXT_SRC_DIR}/src/utils/TypeHelpers.h
    ${TXT_SRC_DIR}/src/utils/WindowsUtils.h
    )

if (WIN32)
    SET(TXT_SRC ${TXT_SRC}
        ${TXT_SRC_DIR}/src/txt/platform_windows.cc
        )
endif()

ADD_LIBRARY(${TARGET_NAME} STATIC ${TXT_SRC})

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH})
TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/third_party)
TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/third_party/skia)
TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/third_party/harfbuzz/src)
TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/third_party/icu/include)
TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${PROJECT_ROOT_PATH}/third_party/flutter/third_party/txt/src)

TARGET_COMPILE_DEFINITIONS(${TARGET_NAME} PUBLIC NOMINMAX)
