set(TEST_PROJECT_NAME "SubscriptionServiceTests")

message(STATUS "Configuring ${TEST_PROJECT_NAME}...")

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(${TEST_PROJECT_NAME}
    ${TEST_SOURCE_FILES}
)

target_link_libraries(${TEST_PROJECT_NAME}
    PRIVATE
        GTest::gtest_main
        SubscriptionService
)

target_include_directories(${TEST_PROJECT_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/SubscriptionService/include"
)

set_target_properties(${TEST_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/tests
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/tests/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/tests/archive
)

include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${TEST_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
