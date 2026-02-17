cmake_minimum_required(VERSION 3.14)
project(WallBall C)

set(CMAKE_C_STANDARD 99)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(WallBall main.c)
target_link_libraries(WallBall raylib)

# アセットをビルドディレクトリにコピー
add_custom_command(TARGET WallBall POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/image $<TARGET_FILE_DIR:WallBall>/image
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sound $<TARGET_FILE_DIR:WallBall>/sound
)
