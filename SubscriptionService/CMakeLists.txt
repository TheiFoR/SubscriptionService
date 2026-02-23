set(LIB_NAME "SubscriptionService")

message(STATUS "Configuring ${LIB_NAME} library...")

# *** Fetch Asio Library ***

include(FetchContent)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-36-0
)

FetchContent_MakeAvailable(asio)

# *** Library Source Files ***

set(SUBSERVICE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
)
file(GLOB_RECURSE HEADER_FILES
    "include/*.hpp"
    "include/*.h"
    "include/*.inl"
)
file(GLOB_RECURSE TEMPLATE_FILES
    "src/*.tpp"
)

message(STATUS "SubService include: ${SUBSERVICE_INCLUDE_DIR}")

# *** Asio Includes ***

set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include")

file (GLOB_RECURSE ASIO_INCLUDE_FILES
    "${ASIO_INCLUDE_DIR}/asio.hpp"
)

message(STATUS "Asio include: ${ASIO_INCLUDE_DIR}")

# *** Create Library Target ***

add_library(${LIB_NAME} SHARED
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${TEMPLATE_FILES}
    ${ASIO_INCLUDE_FILES}
)

target_include_directories(${LIB_NAME} 
    PUBLIC
        "${SUBSERVICE_INCLUDE_DIR}"
        "${ASIO_INCLUDE_DIR}"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_definitions(${LIB_NAME} 
    PRIVATE
        SUBSCRIPTIONSERVICE_EXPORTS
        ASIO_STANDALONE
)

set_target_properties(${LIB_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/archive
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 20)
endif()
