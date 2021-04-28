cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies/fmt EXCLUDE_FROM_ALL)

find_package (OpenGL REQUIRED)
#find_package(fmt)
set(LIBS ${PROJECT_SOURCE_DIR}/lib/glfw3.lib fmt::fmt)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(1.GetStarted)