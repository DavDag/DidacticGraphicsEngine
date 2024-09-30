# GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For windows
FetchContent_MakeAvailable(googletest)

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
	PRIVATE GTest::gtest_main
	PRIVATE GTest::gmock_main
)

# GTest
include(GoogleTest)
gtest_discover_tests(dge_lib_tests)
