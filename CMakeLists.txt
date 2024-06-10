cmake_minimum_required(VERSION 3.28)
project(Candytuft)

find_package(OpenGL)
find_package(glfw3)
find_package(Freetype)
find_package(CURL)

set(CMAKE_CXX_STANDARD 26)

include_directories(includes)

add_executable(Candytuft
        main.cpp
        glad.c
        TransparentWindow.cpp
        FontRenderer.cpp
        FontRenderer.hpp
        RenderableCharacter.cpp
        RenderableCharacter.hpp
        Shader.cpp
        Shader.hpp
        Hitokoto.cpp
        Hitokoto.hpp
)
include_directories(${PULSEAUDIO_INCLUDE_DIRS} ${X11_INCLUDE_DIR} ${CURL_INCLUDE_DIR})
target_link_libraries(Candytuft GL glfw pulse pulse-simple ${CURL_LIBRARIES} ${PULSEAUDIO_LIBRARIES} Freetype::Freetype)
