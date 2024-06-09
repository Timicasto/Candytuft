cmake_minimum_required(VERSION 3.28)
project(Candytuft)

find_package(X11)
find_package(OpenGL)
find_package(glfw3)

set(CMAKE_C_STANDARD 26)
set(CMAKE_CXX_STANDARD 26)

include_directories(includes)

add_executable(Candytuft main.cpp
        TransparentWindow.cpp)
include_directories(${PULSEAUDIO_INCLUDE_DIRS} ${X11_INCLUDE_DIR})
target_link_libraries(Candytuft GL glfw pulse pulse-simple ${PULSEAUDIO_LIBRARIES} ${X11_LIBRARIES})
