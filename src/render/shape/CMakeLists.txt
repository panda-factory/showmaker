SET(TARGET_NAME shape)
SET(SHAPE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

SET(SHAPE_SRC
    rectangle.cpp)

if (WIN32)
    SET(SHAPE_SRC ${SHAPE_SRC}
        text.cpp
        ${SHAPE_SRC_DIR}/text/font_collection.cpp
        ${SHAPE_SRC_DIR}/text/paragraph.cpp
        ${SHAPE_SRC_DIR}/text/paragraph_builder.cpp
        ${SHAPE_SRC_DIR}/text/text_editing_value.cpp
        ${SHAPE_SRC_DIR}/text/text_style.cpp)
ELSEIF(ANDROID)

endif()

ADD_LIBRARY(${TARGET_NAME} STATIC ${SHAPE_SRC})

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC
    ${PROJECT_ROOT_PATH}
    ${PROJECT_ROOT_PATH}/src
    ${PROJECT_ROOT_PATH}/third_party
    ${PROJECT_ROOT_PATH}/third_party/flutter
    ${PROJECT_ROOT_PATH}/third_party/skia)

TARGET_LINK_LIBRARIES(${TARGET_NAME} PUBLIC css)
if (WIN32)
    TARGET_LINK_LIBRARIES(${TARGET_NAME} PUBLIC lib_txt)
ELSEIF(ANDROID)

endif()
