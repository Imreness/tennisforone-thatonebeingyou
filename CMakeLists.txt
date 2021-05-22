cmake_minimum_required(VERSION 3.16.0)
project(TFOTOBY VERSION 0.0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSION ON)

add_executable(TFOTOBY code/main.cpp)
target_include_directories(TFOTOBY PRIVATE "h/")
#include("assetpacker/CMakeLists.txt")

#set_target_properties(TFOTOBY PROPERTIES RUNTIME_OUTPUT_DIRECTORY "game/")



add_library(Engine STATIC
    h/glad/glad.h
    h/glad.c 
    h/imgui/imconfig.h
    h/imgui/imgui_internal.h 
    h/imgui/imgui_widgets.cpp
    h/imgui/imstb_rectpack.h 
    h/imgui/imstb_textedit.h
    h/imgui/imstb_truetype.h
    h/imgui/imgui.cpp
    h/imgui/imgui.h
    h/imgui/imgui_draw.cpp
    h/imgui/imgui_impl_opengl3.h
    h/imgui/imgui_impl_opengl3.cpp    
    h/imgui/imgui_impl_glfw.h   
    h/imgui/imgui_impl_glfw.cpp  
)
set_target_properties(Engine PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Engine PRIVATE "h/")

target_link_libraries(TFOTOBY Engine)



if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/assimp-vc141-mtd.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/BulletCollision_Debug.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/BulletDynamics_Debug.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/LinearMath_Debug.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/spdlogd.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/glfw3d.lib)
    endif()
    if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/assimp-vc141-mt.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/BulletCollision.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/BulletDynamics.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/LinearMath.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/spdlog.lib)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/glfw3.lib)
    endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/d_libglfw3.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/d_libspdlogd.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/d_libLinearMath.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/d_libBulletDynamics.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/d_libBulletCollision.a)
        target_link_libraries(TFOTOBY GL dl pthread X11 z)
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/libglfw3.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/libspdlog.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/libLinearMath.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/libBulletDynamics.a)
        target_link_libraries(TFOTOBY ${CMAKE_SOURCE_DIR}/l/libBulletCollision.a)
        target_link_libraries(TFOTOBY GL dl pthread X11 z)
    endif()
endif()
