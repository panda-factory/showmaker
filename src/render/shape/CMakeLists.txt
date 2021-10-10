SET(TARGET_NAME shape)
SET(SHAPE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

SET(SHAPE_SRC
    ${SHAPE_SRC_DIR}/text/font_collection.cpp
    ${SHAPE_SRC_DIR}/text/paragraph.cpp
    ${SHAPE_SRC_DIR}/text/paragraph_builder.cpp
    ${SHAPE_SRC_DIR}/text/text_style.cpp)

ADD_LIBRARY(${TARGET_NAME} STATIC ${SHAPE_SRC})

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC
    ${PROJECT_ROOT_PATH}/src
    ${PROJECT_ROOT_PATH}/third_party
    ${PROJECT_ROOT_PATH}/third_party/flutter)

TARGET_LINK_LIBRARIES(${TARGET_NAME} PUBLIC lib_txt css)
