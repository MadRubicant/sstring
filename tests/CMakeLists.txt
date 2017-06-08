set(SOURCES sstring_test.c)

target_link_libraries(sstring)
include_directories("${CMAKE_BINARY_DIR}/include")
add_executable(test ${SOURCES})
