# Create application
add_executable(simple_opengl)

# Add sources
target_sources(
	simple_opengl
	PRIVATE
	FILE_SET CXX_MODULES FILES
	"src/main.ixx"
)

# Link libraries
target_link_libraries(
	simple_opengl
	PRIVATE dge_lib
)
