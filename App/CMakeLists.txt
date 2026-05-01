set(PROJECT_NAME "App")

file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
)
file(GLOB_RECURSE HEADER_FILES
    "src/*.hpp"
    "src/*.h"
)
file(GLOB_RECURSE TEMPLATE_FILES
    "src/*.tpp"
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h
)

message(STATUS "Source files: ${SOURCE_FILES}")
message(STATUS "Header files: ${HEADER_FILES}")
message(STATUS "Template files: ${TEMPLATE_FILES}")

add_executable (${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${TEMPLATE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/archive
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE SubscriptionService
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
