
ADD_SUBDIRECTORY(css)
ADD_SUBDIRECTORY(engine)
ADD_SUBDIRECTORY(graphics)
ADD_SUBDIRECTORY(render)
ADD_SUBDIRECTORY(wtf/diagnostics)

SET(WINDOW_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/node/abstract_node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/compositing/scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/compositing/scene_builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/canvas_scope.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/elements/editable_text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/elements/label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/elements/view.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/clip_rect_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/container_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/follower_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/layer_link.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/leader_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/offset_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/picture_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layer/transform_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layout/column.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/painting/paint_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/painting/picture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/painting/picture_recorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/pipeline/render_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/pipeline/render_pipeline.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/drawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/elements/element.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/layout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/shape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/shape/rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/shape/text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_window_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
    )

IF(WIN32)
    SET(WINDOW_SRC ${WINDOW_SRC}
        #platform/windows/gl_window_context_win32.cpp
        platform/windows/window_win32.cpp)

    # using angle
    IF(USING_ANGLE)
        SET(WINDOW_SRC ${WINDOW_SRC}
            platform/windows/angle_gl_window_context.cpp)
    ENDIF()
ENDIF()

IF(BUILDING_SHARED)
    ADD_LIBRARY(window SHARED ${WINDOW_SRC})
    TARGET_COMPILE_DEFINITIONS(window PRIVATE BUILDING_SHARED=1)
ELSE()
    ADD_LIBRARY(window STATIC ${WINDOW_SRC})
ENDIF()

if (WIN32)
    TARGET_COMPILE_DEFINITIONS(window PRIVATE OS_WIN=1)
endif()

TARGET_INCLUDE_DIRECTORIES(window PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_ROOT_PATH}
    ${PROJECT_ROOT_PATH}/third_party/angle/include
    ${PROJECT_ROOT_PATH}/third_party/skia
    ${PROJECT_ROOT_PATH}/third_party)

TARGET_LINK_DIRECTORIES(window PUBLIC ${PROJECT_ROOT_PATH}/third_party/angle/libs)
TARGET_LINK_DIRECTORIES(window PUBLIC ${PROJECT_ROOT_PATH}/third_party/skia/libs)
TARGET_LINK_LIBRARIES(window PUBLIC libEGL.dll.lib libGLESv2.dll.lib skia.dll.lib skshaper.dll.lib ext_convertUTF engine lib_txt shape graphics diagnostic)