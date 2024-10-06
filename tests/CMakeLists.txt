# Create application
add_executable(dge_lib_tests)

# Add sources
target_sources(
        dge_lib_tests
        PRIVATE
        FILE_SET CXX_MODULES FILES
        "src/core/types.tests.ixx"
        "src/core/assert.tests.ixx"
        "src/core/log.tests.ixx"
        "src/core/core.tests.ixx"
        "src/math/vec2.tests.ixx"
        "src/math/vec3.tests.ixx"
        "src/math/vec4.tests.ixx"
        "src/math/math.tests.ixx"
        "src/main.tests.ixx"
)

# Link libraries
target_link_libraries(
        dge_lib_tests
        PRIVATE dge_lib
        PRIVATE GTest::gtest
        PRIVATE GTest::gtest_main
        PRIVATE GTest::gmock
        PRIVATE GTest::gmock_main
)

# GTest
enable_testing()
include(GoogleTest)
gtest_discover_tests(dge_lib_tests)