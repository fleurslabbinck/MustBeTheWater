# Get all source files
file(GLOB_RECURSE SRC_FILES "*.cpp")

# Register all .cpp files
idf_component_register(
    SRCS    ${SRC_FILES}
    INCLUDE_DIRS .
)