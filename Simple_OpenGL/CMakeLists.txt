# Create application
add_executable(DGE_sample_opengl)

# Add sources
target_sources(
	DGE_sample_opengl
	PRIVATE
	FILE_SET CXX_MODULES FILES
	"src/main.ixx"
)

# Link libraries
target_link_libraries(
	DGE_sample_opengl
	PRIVATE DGE_lib
)
