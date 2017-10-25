cmake_minimum_required(VERSION 3.8)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Resources/0.png
        Resources/1.png
        Resources/2.png
        View/Window.cpp
        View/Window.h
        View/ViewError.cpp
        View/ViewError.h
        View/Renderer.cpp
        View/Renderer.h
        View/TextureLoader.cpp
        View/TextureLoader.h
        View/MapView.cpp
        View/MapView.h
        View/mainView.cpp
        View/Sprite.cpp
        View/Sprite.h View/SpriteNamesConfig.h View/View.cpp View/View.h View/PortalView.cpp View/PortalView.h View/PortalEntradaView.cpp View/PortalEntradaView.h View/PortalSalidaView.cpp View/PortalSalidaView.h View/FireTowerView.cpp View/FireTowerView.h)

add_executable(TowerDefense ${SOURCE_FILES})

INCLUDE(FindPkgConfig)
#pkg_search_module(SDL2 REQUIRED)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
#target_link_libraries(TowerDefense ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefense ${SDL2IMAGE_LIBRARIES})