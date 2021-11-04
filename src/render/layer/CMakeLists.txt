SET(TARGET_NAME layer)
SET(LAYER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

SET(LAYER_SRC
    ${LAYER_SRC_DIR}/clip_path_layer.cpp
    ${LAYER_SRC_DIR}/clip_rect_layer.cpp
    ${LAYER_SRC_DIR}/clip_rrect_layer.cpp
    ${LAYER_SRC_DIR}/container_layer.cpp
    ${LAYER_SRC_DIR}/follower_layer.cpp
    ${LAYER_SRC_DIR}/layer.cpp
    ${LAYER_SRC_DIR}/layer_link.cpp
    ${LAYER_SRC_DIR}/leader_layer.cpp
    ${LAYER_SRC_DIR}/offset_layer.cpp
    ${LAYER_SRC_DIR}/performance_overlay_layer.cpp
    ${LAYER_SRC_DIR}/picture_layer.cpp
    ${LAYER_SRC_DIR}/transform_layer.cpp)

ADD_LIBRARY(${TARGET_NAME} STATIC ${LAYER_SRC})

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC
    ${PROJECT_ROOT_PATH}
    ${PROJECT_ROOT_PATH}/src
    ${PROJECT_ROOT_PATH}/third_party
    ${PROJECT_ROOT_PATH}/third_party/skia)

TARGET_LINK_LIBRARIES(${TARGET_NAME} PUBLIC)
