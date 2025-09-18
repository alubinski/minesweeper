cmake_minimum_required(VERSION 3.16)
project(Minesweeper VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(engine)
add_subdirectory(minesweeper)

add_executable(Minesweeper
    "main.cpp"
)

target_include_directories(Minesweeper PRIVATE ${CMAKE_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(Minesweeper PRIVATE SDL2 SDL2_image SDL2_ttf engine minesweeper)

if(WIN32)
    target_link_libraries(Minesweeper PRIVATE SDL2main)
endif()

set(AssetsDir "${CMAKE_SOURCE_DIR}/assets")
add_custom_command(TARGET Minesweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${AssetsDir}/Rubik-SemiBold.ttf"
    "${AssetsDir}/flag.png"
    "${AssetsDir}/bomb.png"
    $<TARGET_FILE_DIR:Minesweeper>
    VERBATIM
)
