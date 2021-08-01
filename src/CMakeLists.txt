

SET(WINDOW_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/component/editor/editor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/component/editor/editor_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/component/editor/shape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/component/editor/string_slice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/component/editor/word_boundaries.cpp
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
    ${PROJECT_ROOT_PATH}/third-party/angle/include
    ${PROJECT_ROOT_PATH}/third-party/skia)

TARGET_LINK_DIRECTORIES(window PUBLIC ${PROJECT_ROOT_PATH}/third-party/angle/libs)
TARGET_LINK_DIRECTORIES(window PUBLIC ${PROJECT_ROOT_PATH}/third-party/skia/libs)
TARGET_LINK_LIBRARIES(window PRIVATE libEGL.dll.lib libGLESv2.dll.lib skia.dll.lib skshaper.dll.lib ext_convertUTF)