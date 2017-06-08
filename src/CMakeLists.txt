set(SOURCE_FILES sstring.c sstringio.c)
set(HEADER_FILES sstring.h sstringio.h)


#add_library(sstring ${SOURCE_FILES})
add_library(sstring STATIC ${SOURCE_FILES})

install(TARGETS sstring
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static)

file(COPY ${HEADER_FILES} DESTINATION "${CMAKE_BINARY_DIR}/include" USE_SOURCE_PERMISSIONS)
