
SET(TARGET_NAME diagnostic)
SET(DIAGNOSTIC_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(DIAGNOSTIC_SRC
    ${DIAGNOSTIC_SRC_DIR}/diagnostic_properties_builder.cpp
    ${DIAGNOSTIC_SRC_DIR}/diagnosticable.cpp
    ${DIAGNOSTIC_SRC_DIR}/diagnosticable_tree.cpp
    ${DIAGNOSTIC_SRC_DIR}/diagnostics_node.cpp
    ${DIAGNOSTIC_SRC_DIR}/diagnostics_property.cpp
    ${DIAGNOSTIC_SRC_DIR}/diagnostics_tree_style.cpp
    ${DIAGNOSTIC_SRC_DIR}/prefixed_string_builder.cpp
    ${DIAGNOSTIC_SRC_DIR}/text_tree_configuration.cpp
    ${DIAGNOSTIC_SRC_DIR}/text_tree_renderer.cpp
    )

ADD_LIBRARY(${TARGET_NAME} STATIC ${DIAGNOSTIC_SRC})

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC
    ${PROJECT_ROOT_PATH}
    ${PROJECT_ROOT_PATH}/src
    ${PROJECT_ROOT_PATH}/third_party)