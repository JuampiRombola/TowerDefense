cmake_minimum_required(VERSION 3.8)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_V
        Resources/0.png Resources/1.png Resources/2.png View/Window.cpp
        View/Window.h View/ViewError.cpp View/ViewError.h View/Renderer.cpp
        View/Renderer.h View/TextureLoader.cpp View/TextureLoader.h
        View/MapView.cpp View/MapView.h View/mainView.cpp View/Sprite.cpp
        View/Sprite.h View/SpriteNamesConfig.h View/View.cpp View/View.h
        View/PortalView.cpp View/PortalView.h View/PortalEntradaView.cpp
        View/PortalEntradaView.h View/PortalSalidaView.cpp
        View/PortalSalidaView.h View/FireTowerView.cpp View/FireTowerView.h)

set(SOURCE_FILES_E
        Resources/0.png Resources/1.png Resources/2.png Resources/100.png
        Resources/101.png Resources/102.png Resources/103.png Resources/104.png
        Resources/105.png Resources/106.png Resources/107.png
        Resources/108.png View/Window.cpp View/Window.h View/ViewError.cpp
        View/ViewError.h View/Renderer.cpp
        View/Renderer.h View/TextureLoader.cpp View/TextureLoader.h
        View/MapView.cpp View/MapView.h View/mainEditor.cpp View/Sprite.cpp
        View/Sprite.h View/SpriteNamesConfig.h View/View.cpp View/View.h
        View/PortalView.cpp View/PortalView.h View/PortalEntradaView.cpp
        View/PortalEntradaView.h View/PortalSalidaView.cpp
        View/PortalSalidaView.h View/FireTowerView.cpp View/FireTowerView.h
        View/MousePosition.cpp View/MousePosition.h View/Editor.cpp
        View/Editor.h View/KeyboardInput.cpp View/KeyboardInput.h
        View/Button.cpp View/Button.h View/AgregarEnemigoButton.cpp View/AgregarEnemigoButton.h View/EliminarEnemigoButton.cpp View/EliminarEnemigoButton.h View/EliminarHordaButton.cpp View/EliminarHordaButton.h View/NuevaHordaButton.cpp View/NuevaHordaButton.h View/SuperficieButton.cpp View/SuperficieButton.h View/ToggleButton.cpp View/ToggleButton.h View/Buttons.cpp View/Buttons.h View/TextInput.cpp View/TextInput.h)

add_executable(TowerDefenseView ${SOURCE_FILES_V})
add_executable(TowerDefenseEditor ${SOURCE_FILES_E})

INCLUDE(FindPkgConfig)
#pkg_search_module(SDL2 REQUIRED)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
#target_link_libraries(TowerDefense ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefenseView ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefenseEditor ${SDL2IMAGE_LIBRARIES})