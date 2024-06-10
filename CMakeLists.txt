cmake_minimum_required(VERSION 3.28)
project(Candytuft)

find_package(X11)
find_package(OpenGL)
find_package(glfw3)
find_package(Freetype)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 26)

include_directories(includes)

add_executable(Candytuft main.cpp
        TransparentWindow.cpp
        FontRenderer.cpp
        FontRenderer.hpp
        RenderableCharacter.cpp
        RenderableCharacter.hpp
        Shader.cpp
        Shader.hpp
        glad.c)
include_directories(${PULSEAUDIO_INCLUDE_DIRS} ${X11_INCLUDE_DIR})
target_link_libraries(Candytuft GL glfw pulse Xrender pulse-simple ${PULSEAUDIO_LIBRARIES} ${X11_LIBRARIES} Freetype::Freetype)
