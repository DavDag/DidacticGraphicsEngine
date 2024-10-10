# Create a library
add_library(dge_lib)

# Add sources
target_sources(
	dge_lib
	PUBLIC
	FILE_SET CXX_MODULES FILES
	"src/core/types.ixx"
	"src/core/log.ixx"
	"src/core/assert.ixx"
	"src/core/core.ixx"
	"src/math/vec2.ixx"
	"src/math/vec3.ixx"
	"src/math/vec4.ixx"
	"src/math/math.ixx"
	"src/engine.ixx"
)

# Include libs
target_include_directories(
	dge_lib
	PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

