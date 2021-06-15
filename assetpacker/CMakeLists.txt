add_executable(assetpacker assetpacker/main_asset.cpp)
target_include_directories(assetpacker PRIVATE "h/")
target_include_directories(assetpacker PRIVATE "assetpacker/")
target_include_directories(assetpacker PRIVATE "code/")
set_target_properties(assetpacker PROPERTIES RUNTIME_OUTPUT_DIRECTORY "assetpacker/")

add_library(assetengine STATIC
    assetpacker/uiloader.cpp
    assetpacker/assetloader.cpp
    code/core/binaryfile.hpp
    code/core/binaryfile.cpp
)
set_target_properties(assetengine PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(assetengine PRIVATE "h/")
target_include_directories(assetengine PRIVATE "assetpacker/")
target_include_directories(assetengine PRIVATE "code/")

target_link_libraries(assetpacker assetengine)

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        target_link_libraries(assetpacker ${CMAKE_SOURCE_DIR}/l/assimp-vc141-mtd.lib)
    endif()
    if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
        target_link_libraries(assetpacker ${CMAKE_SOURCE_DIR}/l/assimp-vc141-mt.lib)
    endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    target_link_libraries(assetpacker GL dl pthread X11 z assimp)
endif()
