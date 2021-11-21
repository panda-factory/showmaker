SET(TARGET_NAME window)
SET(WINDOW_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

SET(WINDOW_SRC
    ${WINDOW_SRC_DIR}/gl_window_context.cpp
    ${WINDOW_SRC_DIR}/window_context.cpp
    ${WINDOW_SRC_DIR}/window.cpp)

IF(WIN32)
    SET(WINDOW_SRC ${WINDOW_SRC}
        platform/win32/gl_window_context_win32.cpp
        platform/win32/window_win32.cpp)

    # using angle
    IF(USING_ANGLE)
        SET(WINDOW_SRC ${WINDOW_SRC}
            platform/win32/angle_gl_window_context.cpp)
    ENDIF()
ELSEIF(ANDROID)
    SET(WINDOW_SRC ${WINDOW_SRC}
        platform/android/gl_window_context_android.cpp)
ENDIF()

ADD_LIBRARY(${TARGET_NAME} STATIC ${WINDOW_SRC})

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC
    ${PROJECT_ROOT_PATH}
    ${PROJECT_ROOT_PATH}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_ROOT_PATH}/third_party
    ${PROJECT_ROOT_PATH}/third_party/skia
    ${PROJECT_ROOT_PATH}/third_party/angle/include)

TARGET_LINK_LIBRARIES(${TARGET_NAME} PUBLIC)
