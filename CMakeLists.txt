cmake_minimum_required(VERSION 3.6)
project(Spaceshit)

set(CMAKE_CXX_STANDARD 11)

set( CMAKE_MODULE_PATH /usr/local/include/SOIL/)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)


include_directories(/usr/include/SOIL)
link_directories(/usr/lib/SOIL)

include_directories(${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE INCLUDE_FILES "include/*.h")

add_executable(Spaceshit ${SOURCE_FILES})
target_link_libraries(Spaceshit
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        SOIL)