
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
add_library(minesweeper ${SOURCES})

target_include_directories(minesweeper PUBLIC ${CMAKE_SOURCE_DIR})
