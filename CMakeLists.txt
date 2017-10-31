cmake_minimum_required(VERSION 3.8)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_V
        View/Common/Window.cpp
        View/Common/Window.h View/Common/ViewError.cpp View/Common/ViewError.h View/Common/Renderer.cpp
        View/Common/Renderer.h View/Common/TextureLoader.cpp View/Common/TextureLoader.h
        View/Model/MapView.cpp View/Model/MapView.h View/mainView.cpp View/Common/Sprite.cpp
        View/Common/Sprite.h View/Common/SpriteNamesConfig.h View/Common/View.cpp View/Common/View.h
        View/Model/PortalView.cpp View/Model/PortalView.h View/Model/PortalEntradaView.cpp
        View/Model/PortalEntradaView.h View/Model/PortalSalidaView.cpp
        View/Model/PortalSalidaView.h View/Model/FireTowerView.cpp View/Model/FireTowerView.h
        View/Model/UnitView.cpp View/Model/UnitView.h)

set(SOURCE_FILES_E
        View/Common/Window.cpp View/Common/Window.h View/Common/ViewError.cpp
        View/Common/ViewError.h View/Common/Renderer.cpp
        View/Common/Renderer.h View/Common/TextureLoader.cpp View/Common/TextureLoader.h
        View/Model/MapView.cpp View/Model/MapView.h View/mainEditor.cpp View/Common/Sprite.cpp
        View/Common/Sprite.h View/Common/SpriteNamesConfig.h View/Common/View.cpp View/Common/View.h
        View/Model/PortalView.cpp View/Model/PortalView.h View/Model/PortalEntradaView.cpp
        View/Model/PortalEntradaView.h View/Model/PortalSalidaView.cpp
        View/Model/PortalSalidaView.h View/Model/FireTowerView.cpp View/Model/FireTowerView.h
        View/Common/MousePosition.cpp View/Common/MousePosition.h View/Editor/Editor.cpp
        View/Editor/Editor.h View/Common/KeyboardInput.cpp View/Common/KeyboardInput.h
        View/Editor/Button.cpp View/Editor/Button.h View/Editor/AgregarEnemigoButton.cpp
        View/Editor/AgregarEnemigoButton.h View/Editor/EliminarEnemigoButton.cpp
        View/Editor/EliminarEnemigoButton.h View/Editor/EliminarHordaButton.cpp
        View/Editor/EliminarHordaButton.h View/Editor/NuevaHordaButton.cpp
        View/Editor/NuevaHordaButton.h View/Editor/SuperficieButton.cpp View/Editor/SuperficieButton.h
        View/Editor/ToggleButton.cpp View/Editor/ToggleButton.h View/Editor/Buttons.cpp
        View/Editor/Buttons.h View/Common/Text.cpp View/Common/Text.h View/Common/Image.cpp
        View/Common/Image.h View/Editor/DoNothingButton.cpp View/Editor/DoNothingButton.h
        View/Editor/ContadorEnemigosInput.cpp View/Editor/ContadorEnemigosInput.h)

add_executable(TowerDefenseView ${SOURCE_FILES_V})
add_executable(TowerDefenseEditor ${SOURCE_FILES_E})

INCLUDE(FindPkgConfig)
#pkg_search_module(SDL2 REQUIRED)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
#target_link_libraries(TowerDefense ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefenseView ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefenseEditor ${SDL2IMAGE_LIBRARIES})