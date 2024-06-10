cmake_minimum_required(VERSION 3.28)
project(Candytuft)

set(CMAKE_CXX_STANDARD 26)

include_directories(includes)

add_executable(Candytuft
        main.cpp
        glad.c
        TransparentWindow.cpp
        FontRenderer.cpp
        RenderableCharacter.cpp
        Shader.cpp
        modules/Hitokoto.cpp
        modules/SystemMonitor.cpp
        modules/SystemMonitor.hpp
)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(OpenGL)
    find_package(glfw3)
    find_package(Freetype)
    find_package(CURL)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(Candytuft GL glfw pulse pulse-simple ${CURL_LIBRARIES} Freetype::Freetype)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    link_directories(./libs_win64)
    target_link_libraries(Candytuft libglfw3dll.a libglfw3.a opengl32 freetype.lib)
    include_directories(./libs_win64/includes)
ENDIF()

configure_file(AlibabaPuHuiTi-2-65-Medium.ttf AlibabaPuHuiTi-2-65-Medium.ttf COPYONLY)
