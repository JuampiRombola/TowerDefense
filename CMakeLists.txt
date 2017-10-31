cmake_minimum_required(VERSION 3.8)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES_M
        TowerDefenseServer/include/Commands/BuildTowerCommand.h
        TowerDefenseServer/include/Commands/CastSpellCommand.h
        TowerDefenseServer/include/Commands/Command.h
        TowerDefenseServer/include/Commands/UpgradeTowerCommand.h
        TowerDefenseServer/src/Commands/BuildTowerCommand.cpp
        TowerDefenseServer/src/Commands/CastSpellCommand.cpp
        TowerDefenseServer/src/Commands/Command.cpp
        TowerDefenseServer/src/Commands/UpgradeTowerCommand.cpp
        TowerDefenseServer/include/EnviormentUnits/Abmonible.h
        TowerDefenseServer/include/EnviormentUnits/DemonioVerde.h
        TowerDefenseServer/include/EnviormentUnits/EnviormentUnit.h
        TowerDefenseServer/include/EnviormentUnits/Espectro.h
        TowerDefenseServer/include/EnviormentUnits/HalconSangriento.h
        TowerDefenseServer/include/EnviormentUnits/HombreCabra.h
        TowerDefenseServer/include/EnviormentUnits/NoMuerto.h
        TowerDefenseServer/src/EnviormentUnits/Abmonible.cpp
        TowerDefenseServer/src/EnviormentUnits/DemonioVerde.cpp
        TowerDefenseServer/src/EnviormentUnits/EnviormentUnit.cpp
        TowerDefenseServer/src/EnviormentUnits/Espectro.cpp
        TowerDefenseServer/src/EnviormentUnits/HalconSangriento.cpp
        TowerDefenseServer/src/EnviormentUnits/HombreCabra.cpp
        TowerDefenseServer/src/EnviormentUnits/NoMuerto.cpp
        TowerDefenseServer/include/Exceptions/IncompletePathException.h
        TowerDefenseServer/include/Exceptions/NonPlacedUnitCannotStepException.h
        TowerDefenseServer/include/Exceptions/NoSetSpawnTilesException.h
        TowerDefenseServer/include/Exceptions/PositionAlreadyHasTileException.h
        TowerDefenseServer/include/Exceptions/SolidGroundAlreadyHasTowerException.h
        TowerDefenseServer/include/Exceptions/TileCannotSpawnException.h
        TowerDefenseServer/include/Exceptions/TileIsOutOfBoundsException.h
        TowerDefenseServer/include/Exceptions/UnitCannotMoveDiagonallyException.h
        TowerDefenseServer/include/Exceptions/UnitIsAlreadyOnThisTileException.h
        TowerDefenseServer/include/Exceptions/UnitIsNotOnThisTileException.h
        TowerDefenseServer/include/Map/Map.h
        TowerDefenseServer/include/Map/PathTile.h
        TowerDefenseServer/include/Map/SolidGroundTile.h
        TowerDefenseServer/include/Map/Tile.h
        TowerDefenseServer/src/Map/Map.cpp
        TowerDefenseServer/src/Map/PathTile.cpp
        TowerDefenseServer/src/Map/SolidGroundTile.cpp
        TowerDefenseServer/src/Map/Tile.cpp
        TowerDefenseServer/include/Towers/AirProjectile.h
        TowerDefenseServer/include/Towers/AirTower.h
        TowerDefenseServer/include/Towers/FireTower.h
        TowerDefenseServer/include/Towers/FireProjectile.h
        TowerDefenseServer/include/Towers/GroundProjectile.h
        TowerDefenseServer/include/Towers/GroundTower.h
        TowerDefenseServer/include/Towers/Projectile.h
        TowerDefenseServer/include/Towers/Tower.h
        TowerDefenseServer/include/Towers/WaterTower.h
        TowerDefenseServer/include/Towers/WaterProjectile.h
        TowerDefenseServer/include/GameConfiguration.h
        TowerDefenseServer/include/Helpers.h
        TowerDefenseServer/include/TowerDefenseGame.h
        TowerDefenseServer/src/GameConfiguration.cpp
        TowerDefenseServer/src/main.cpp
        TowerDefenseServer/src/TowerDefenseGame.cpp
        TowerDefenseServer/src/Towers/AirProjectile.cpp
        TowerDefenseServer/src/Towers/AirTower.cpp
        TowerDefenseServer/src/Towers/FireProjectile.cpp
        TowerDefenseServer/src/Towers/FireTower.cpp
        TowerDefenseServer/src/Towers/GroundProjectile.cpp
        TowerDefenseServer/src/Towers/GroundTower.cpp
        TowerDefenseServer/src/Towers/Projectile.cpp
        TowerDefenseServer/src/Towers/Tower.cpp
        TowerDefenseServer/src/Towers/WaterProjectile.cpp
        TowerDefenseServer/src/Towers/WaterTower.cpp
        TowerDefenseServer/include/ViewModels/CommandVM.h
        TowerDefenseServer/include/ViewModels/ProjectileVM.h
        TowerDefenseServer/include/ViewModels/TowerVM.h
        TowerDefenseServer/include/ViewModels/UnitVM.h)

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
add_executable(TowerDefenseModel ${SOURCE_FILES_M})

INCLUDE(FindPkgConfig)
#pkg_search_module(SDL2 REQUIRED)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
#target_link_libraries(TowerDefense ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefenseView ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefenseEditor ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TowerDefenseModel yaml-cpp)