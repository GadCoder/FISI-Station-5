cmake_minimum_required(VERSION 3.18)
project("FISI STATION 5" VERSION 1.0)


find_package(PkgConfig REQUIRED)
#SFML
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
#WX
find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(X11 REQUIRED) # Make sure x is there 


pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${X11_INCLUDE_DIR})

#GTK
set (GTK ${GTK_LIBRARIES} )
link_directories(${GTK_LIBRARY_DIRS})
include_directories(${GTK_INCLUDE_DIRS})
include(${wxWidgets_USE_FILE})
add_definitions(${GTK_CFLAGS_OTHER})


add_executable(
        FISI_Station
        src/CastilloLauncher.cpp
        src/main.cpp
        src/MainFrame.cpp
        src/RocotoBall.cpp
        src/RocotoBar.cpp
        src/RocotoBricks.cpp
        src/RocotoLauncher.cpp
        src/RocotoScore.cpp
        src/RocotoTextures.cpp
        src/ScoreFrame.cpp
        src/Snake.cpp
        src/SnakeFood.cpp
        src/SnakeLauncher.cpp
        src/SnakeTextures.cpp
        src/StartFrame.cpp
        )
target_include_directories(FISI_Station PRIVATE "${PROJECT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/content")
target_link_libraries(FISI_Station PRIVATE sfml-graphics) 
target_link_libraries(FISI_Station PRIVATE sfml-audio) 
target_link_libraries(FISI_Station PRIVATE ${wxWidgets_LIBRARIES} ${GTK}) 
target_link_libraries(FISI_Station PRIVATE /usr/lib/x86_64-linux-gnu/libX11.so) # x11 linking misses this stuff!
target_link_libraries(FISI_Station PRIVATE /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1)
target_link_libraries(FISI_Station PRIVATE ${X11_LIBRARIES}) # x11 !


