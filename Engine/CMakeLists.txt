# Create a library
add_library(dge_lib)

# Copy STD Files in a local folder
set(StdFiles "${VCToolsInstallDir}/modules/std.ixx" "${VCToolsInstallDir}/modules/std.compat.ixx")
file(COPY ${StdFiles} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/ext/std")

target_sources(
	dge_lib
	PUBLIC
	FILE_SET CXX_MODULES FILES
	"ext/std/std.ixx"
	"ext/std/std.compat.ixx"
)

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

