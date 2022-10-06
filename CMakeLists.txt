cmake_minimum_required(VERSION 3.23)
project(ironEngine)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(include/metal-cmake)

include_directories("src")

include_directories("/usr/local/Cellar/llvm/15.0.0/include/c++/v1")
link_directories("/usr/local/Cellar/llvm/15.0.0/lib/c++")


file(GLOB SRC_FILES CONFIGURE_DEPENDS
        "src/*/*.cpp"
        "src/*.cpp"
        )


add_executable(ironEngine ${SRC_FILES})
target_link_libraries(ironEngine METAL_CPP)
