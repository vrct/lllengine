cmake_minimum_required(VERSION 3.7)
project(lllengine)

#set(CMAKE_CXX_STANDARD 11)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS lib)
find_library(SDL2_LIBRARY NAME SDL2 HINTS lib)

find_file(SDL2_IMAGE_INCLUDE_DIR NAME SDL_image.h HINTS lib)
find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image HINTS lib)


find_file(SDL2_IMAGE_INCLUDE_DIR NAME SDL_image.h HINTS lib)
find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image HINTS lib)

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(lllengine ${SOURCES})

target_include_directories(lllengine PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(lllengine ${SDL2_LIBRARY})

target_include_directories(lllengine PUBLIC ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(lllengine ${SDL2_IMAGE_LIBRARY})

target_include_directories(lllengine PUBLIC lib/glew-2.2.0/include/GL)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
#target_link_libraries(lllengine ${OPENGL_LIBRARIES})

if(APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
endif(APPLE)

set_property(TARGET lllengine PROPERTY CXX_STANDARD 11)

target_link_libraries(lllengine ${OPENGL_LIBRARIES} ${EXTRA_LIBS} GLEW::GLEW)
