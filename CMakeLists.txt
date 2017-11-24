cmake_minimum_required(VERSION 3.5)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES_SERVER
        Common/SocketWrapper.cpp
        Common/SocketWrapper.h
        Common/ClientDisconnectedException.h
        Server/include/Exceptions/PlayerLeftLobbyHeWasntInException.h
        Server/include/Exceptions/PlayerStateInLobbyAndHasNoLobbySet.h
        Common/SocketConnectionException.h
        Server/include/Lobbies/Lobby.h
        Server/src/Lobbies/Lobby.cpp
        Server/include/Lobbies/LobbyManager.h
        Server/src/Lobbies/LobbyManager.cpp
        Server/include/Notifications/InvalidLogInNotification.h
        Server/include/Notifications/GameStartedNotification.h
        Server/include/Notifications/LeftLobbyNotification.h
        Server/include/Notifications/LobbyJoinedNotification.h
        Server/include/Notifications/LoggedInNotification.h
        Server/include/Notifications/NewLobbyNotification.h
        Server/include/Notifications/Notification.h
        Server/include/Notifications/PlayerLeftLobbyNotification.h
        Server/src/Notifications/InvalidLoginNotification.cpp
        Server/src/Notifications/LeftLobbyNotification.cpp
        Server/src/Notifications/LobbyJoinedNotification.cpp
        Server/src/Notifications/LoggedInNotification.cpp
        Server/src/Notifications/GameStartedNotification.cpp
        Server/src/Notifications/NewLobbyNotification.cpp
        Server/src/Notifications/Notification.cpp
        Server/src/Notifications/PlayerLeftLobbyNotification.cpp
        Server/src/Notifications/PlayerPickedSpellNotification.cpp
        Server/src/Notifications/PlayerUnpickedSpellNotification.cpp
        Server/include/Notifications/PlayerPickedSpellNotification.h
        Server/include/Notifications/PlayerUnpickedSpellNotification.h
        Server/src/PlayerProxy.cpp
        Server/src/ServerSocket.cpp
        Server/src/TFServer.cpp
        Server/include/PlayerProxy.h
        Server/include/ServerSocket.h
        Server/include/TFServer.h
        Server/include/ThreadSafeQueue.h
        Server/include/GameModel/Commands/BuildTowerCommand.h
        Server/include/GameModel/Commands/CastSpellCommand.h
        Server/include/GameModel/Commands/Command.h
        Server/include/GameModel/Commands/UpgradeTowerCommand.h
        Server/src/GameModel/Commands/BuildTowerCommand.cpp
        Server/src/GameModel/Commands/CastSpellCommand.cpp
        Server/src/GameModel/Commands/Command.cpp
        Server/src/GameModel/Commands/UpgradeTowerCommand.cpp
        Server/include/GameModel/EnviormentUnits/Abmonible.h
        Server/include/GameModel/EnviormentUnits/DemonioVerde.h
        Server/include/GameModel/EnviormentUnits/EnviormentUnit.h
        Server/include/GameModel/EnviormentUnits/Espectro.h
        Server/include/GameModel/EnviormentUnits/HalconSangriento.h
        Server/include/GameModel/EnviormentUnits/HombreCabra.h
        Server/include/GameModel/EnviormentUnits/NoMuerto.h
        Server/src/GameModel/EnviormentUnits/Abmonible.cpp
        Server/src/GameModel/EnviormentUnits/DemonioVerde.cpp
        Server/src/GameModel/EnviormentUnits/EnviormentUnit.cpp
        Server/src/GameModel/EnviormentUnits/Espectro.cpp
        Server/src/GameModel/EnviormentUnits/HalconSangriento.cpp
        Server/src/GameModel/EnviormentUnits/HombreCabra.cpp
        Server/src/GameModel/EnviormentUnits/NoMuerto.cpp
        Server/include/GameModel/Exceptions/IncompletePathException.h
        Server/include/GameModel/Exceptions/NonPlacedUnitCannotStepException.h
        Server/include/GameModel/Exceptions/NoSetSpawnTilesException.h
        Server/include/GameModel/Exceptions/PositionAlreadyHasTileException.h
        Server/include/GameModel/Exceptions/SolidGroundAlreadyHasTowerException.h
        Server/include/GameModel/Exceptions/TileCannotSpawnException.h
        Server/include/GameModel/Exceptions/TileIsOutOfBoundsException.h
        Server/include/GameModel/Exceptions/UnitCannotMoveDiagonallyException.h
        Server/include/GameModel/Exceptions/UnitIsAlreadyOnThisTileException.h
        Server/include/GameModel/Exceptions/UnitIsNotOnThisTileException.h
        Server/include/GameModel/Map/Map.h
        Server/include/GameModel/Map/PathTile.h
        Server/include/GameModel/Map/SolidGroundTile.h
        Server/include/GameModel/Map/Tile.h
        Server/src/GameModel/Map/Map.cpp
        Server/src/GameModel/Map/PathTile.cpp
        Server/src/GameModel/Map/SolidGroundTile.cpp
        Server/src/GameModel/Map/Tile.cpp
        Server/include/GameModel/Towers/AirProjectile.h
        Server/include/GameModel/Towers/AirTower.h
        Server/include/GameModel/Towers/FireTower.h
        Server/include/GameModel/Towers/FireProjectile.h
        Server/include/GameModel/Towers/GroundProjectile.h
        Server/include/GameModel/Towers/GroundTower.h
        Server/include/GameModel/Towers/Projectile.h
        Server/include/GameModel/Towers/Tower.h
        Server/include/GameModel/Towers/WaterTower.h
        Server/include/GameModel/Towers/WaterProjectile.h
        Server/include/GameModel/Configuration.h
        Server/include/GameModel/Helpers.h
        Server/include/GameModel/TowerDefenseGame.h
        Server/include/GameModel/GameNotifications/GameNotification.h
        Server/include/GameModel/GameNotifications/SpellCastedGameNotification.h
        Server/include/GameModel/GameNotifications/UnitPositionGameNotification.h
        Server/include/GameModel/GameNotifications/UnitDiedGameNotification.h
        Server/include/GameModel/GameNotifications/ChatMessageNotification.h
        Server/include/GameModel/GameNotifications/TowerPlacedGameNotification.h
        Server/include/GameModel/Hordes/Horde.h
        Server/src/GameModel/Hordes/Horde.cpp
        Server/include/GameModel/Hordes/HordeManager.h
        Server/src/GameModel/Hordes/HordeManager.cpp
        Server/src/GameModel/GameNotifications/GameNotification.cpp
        Server/src/GameModel/GameNotifications/ChatMessageNotification.cpp
        Server/src/GameModel/GameNotifications/UnitDiedGameNotification.cpp
        Server/src/GameModel/GameNotifications/UnitPositionGameNotification.cpp
        Server/src/GameModel/GameNotifications/TowerPlacedGameNotification.cpp
        Server/src/GameModel/GameNotifications/SpellCastedGameNotification.cpp
        Server/src/GameModel/Configuration.cpp
        Server/src/GameModel/TowerDefenseGame.cpp
        Server/src/GameModel/Towers/AirProjectile.cpp
        Server/src/GameModel/Towers/AirTower.cpp
        Server/src/GameModel/Towers/FireProjectile.cpp
        Server/src/GameModel/Towers/FireTower.cpp
        Server/src/GameModel/Towers/GroundProjectile.cpp
        Server/src/GameModel/Towers/GroundTower.cpp
        Server/src/GameModel/Towers/Projectile.cpp
        Server/src/GameModel/Towers/Tower.cpp
        Server/src/GameModel/Towers/WaterProjectile.cpp
        Server/src/GameModel/Towers/WaterTower.cpp
        Server/include/GameModel/ViewModels/CommandVM.h
        Server/include/GameModel/ViewModels/ProjectileVM.h
        Server/include/GameModel/ViewModels/TowerVM.h
        Server/include/GameModel/ViewModels/UnitVM.h
        Server/src/Notifications/PlayerLeaveNotification.cpp
        Server/include/Notifications/PlayerLeaveNotification.h
        Server/src/GameModel/GameNotifications/UnitCreatedGameNotification.cpp
        Server/include/GameModel/GameNotifications/UnitCreatedGameNotification.h
        Server/src/GameModel/GameNotifications/GameOverGameNotification.cpp
        Server/include/GameModel/GameNotifications/GameOverGameNotification.h
        Server/src/GameModel/GameNotifications/ProjectileFiredGameNotification.cpp
        Server/include/GameModel/GameNotifications/ProjectileFiredGameNotification.h
        Server/src/GameModel/ClientCooldownManager.cpp
        Server/include/GameModel/ClientCooldownManager.h
        Server/src/GameModel/GameNotifications/GameModelStartedRunningNotification.cpp
        Server/include/GameModel/GameNotifications/GameModelStartedRunningNotification.h
        Server/src/GameModel/GameNotifications/MapTransferNotification.cpp
        Server/include/GameModel/GameNotifications/MapTransferNotification.h
        Server/src/GameModel/GameNotifications/ChatMessageNotification.cpp
        Server/include/GameModel/GameNotifications/ChatMessageNotification.h
        Server/src/GameModel/GameNotifications/HordeUpdateGameNotification.cpp
        Server/include/GameModel/GameNotifications/HordeUpdateGameNotification.h Server/src/GameModel/GameNotifications/TowerGainedExperienceGameNotification.cpp Server/include/GameModel/GameNotifications/TowerGainedExperienceGameNotification.h Server/src/GameModel/GameNotifications/TowerUpgradedGameNotification.cpp Server/include/GameModel/GameNotifications/TowerUpgradedGameNotification.h Server/src/Notifications/MapPickedNotification.cpp Server/include/Notifications/MapPickedNotification.h)

set(SOURCE_FILES_CLIENT
        Client/src/NetCommands/UpgradeTowerNetCommand.cpp
        Client/include/NetCommands/UpgradeTowerNetCommand.h

        Client/View/Common/Window.cpp
        Client/View/Common/Window.h
        Client/View/Common/Renderer.cpp
        Client/View/Common/ViewError.h
        Client/View/Common/ViewError.cpp
        Client/View/Common/Renderer.h
        Client/View/Common/TextureLoader.cpp
        Client/View/Common/TextureLoader.h
        Client/View/Common/Sprite.cpp
        Client/View/Common/Sprite.h
        Client/View/Common/SpriteNamesConfig.h
        Client/View/Common/View.cpp
        Client/View/Common/View.h
        Client/View/Common/AnimatedSprite.cpp
        Client/View/Common/AnimatedSprite.h
        Client/View/Common/Image.cpp
        Client/View/Common/Image.h
        Client/View/Common/Button.cpp
        Client/View/Common/Button.h
        Client/View/Common/MousePosition.cpp
        Client/View/Common/MousePosition.h
        Client/View/Model/MapView.cpp
        Client/View/Model/MapView.h
        Client/View/Model/PortalView.cpp
        Client/View/Model/PortalView.h
        Client/View/Model/PortalEntradaView.cpp
        Client/View/Model/PortalEntradaView.h
        Client/View/Model/PortalSalidaView.cpp
        Client/View/Model/PortalSalidaView.h
        Client/View/Model/TowerView.cpp
        Client/View/Model/TowerView.h
        Client/View/Model/UnitView.cpp
        Client/View/Model/UnitView.h
        Client/View/Model/ShotView.cpp
        Client/View/Model/ShotView.h
        Client/View/Model/SpellView.cpp
        Client/View/Model/SpellView.h
        Client/View/Model/ModelView.cpp
        Client/View/Model/ModelView.h
        Client/View/Model/DepthLevel.cpp
        Client/View/Model/DepthLevel.h
        Client/View/Model/HudView.cpp
        Client/View/Model/HudView.h
        Client/View/Model/ViewConstants.h
        Client/View/Model/GameButtons.cpp
        Client/View/Model/GameButtons.h
        Client/SDLRunner.h
        Client/SDLRunner.cpp
        Common/Lock.cpp Common/Lock.h
        Client/src/NetCommands/ClientBuildTowerCommand.cpp
        Client/include/NetCommands/ClientBuildTowerCommand.h
        Client/View/Model/ChatView.cpp
        Client/View/Model/ChatView.h
        Client/View/Model/DepthLevelError.cpp
        Client/View/Model/DepthLevelError.h
        Client/View/Model/TextView.cpp
        Client/View/Model/TextView.h
        Client/View/Model/UpRightButton.cpp
        Client/View/Model/UpRightButton.h
        Client/src/NetCommands/PlayerLoadedGameCommand.cpp
        Client/include/NetCommands/PlayerLoadedGameCommand.h
        Client/src/NetCommands/LoadMapCommand.cpp
        Client/include/NetCommands/LoadMapCommand.h
        Client/src/NetCommands/ChatMessageCommand.cpp
        Client/include/NetCommands/ChatMessageCommand.h
        Client/View/Common/Announcement.cpp
        Client/View/Common/Announcement.h
        Client/View/Common/MusicLoader.cpp
        Client/View/Common/MusicLoader.h
        Client/View/Common/MusicNamesConfig.h
        Client/View/Model/ProgressBarView.cpp
        Client/View/Model/ProgressBarView.h
        Client/View/Model/GameButton.cpp
        Client/View/Model/GameButton.h
        Client/View/Model/InstantButton.cpp
        Client/View/Model/InstantButton.h
        Client/View/Model/UpgradeView.cpp
        Client/View/Model/UpgradeView.h
        Client/View/Model/WaitActionButton.cpp
        Client/View/Model/WaitActionButton.h
        Client/View/Model/PadlockButton.cpp
        Client/View/Model/PadlockButton.h
        Client/View/Model/ExitView.cpp
        Client/View/Model/ExitView.h
        Client/View/Common/MouseMovement.cpp
        Client/View/Common/MouseMovement.h
        Client/View/Common/MusicPlayer.cpp
        Client/View/Common/MusicPlayer.h
        Client/View/Common/SoundEffect.cpp
        Client/View/Common/SoundEffect.h)


set(SOURCE_FILES_CLIENT_GTK
        Client/GTKRunner.h
        Client/GTKRunner.cpp



        Client/src/ClientSocket.cpp
        Client/include/ClientSocket.h
        Common/SocketWrapper.cpp
        Common/SocketWrapper.h
        Common/SocketConnectionException.h
        Common/ClientDisconnectedException.h


        Client/src/SDLNotifications/SDLNotification.cpp
        Client/src/GTKNotifications/JoinedLobbyGTKNotification.cpp
        Client/src/GTKNotifications/LeftLobbyGTKNotification.cpp
        Client/src/GTKNotifications/PickedSpellGTKNotification.cpp
        Client/src/GTKNotifications/OtherPickedSpellGTKNotification.cpp
        Client/src/GTKNotifications/NewLobbyGTKNotification.cpp
        Client/src/GTKNotifications/GameStartedGTKNotification.cpp
        Client/src/GTKNotifications/PlayerLeftLobbyGTKNotification.cpp
        Client/src/GTKNotifications/LobbyPickedMapGTKNotification.cpp
        Client/src/NotificationReciever.cpp

        Client/include/GTKNotifications/LobbyPickedMapGTKNotification.h
        Client/include/SDLNotifications/SDLNotification.h
        Client/include/GTKNotifications/JoinedLobbyGTKNotification.h
        Client/include/GTKNotifications/PickedSpellGTKNotification.h
        Client/include/GTKNotifications/GameStartedGTKNotification.h
        Client/include/GTKNotifications/OtherPickedSpellGTKNotification.h
        Client/include/GTKNotifications/LeftLobbyGTKNotification.h
        Client/include/GTKNotifications/NewLobbyGTKNotification.h
        Client/include/GTKNotifications/PlayerLeftLobbyGTKNotification.h
        Client/include/NotificationReciever.h

        Client/src/Lobbies/ClientLobbyManager.cpp
        Client/src/Lobbies/OtherPlayer.cpp
        Client/src/Lobbies/Lobby.cpp
        Client/include/Lobbies/ClientLobbyManager.h
        Client/include/Lobbies/OtherPlayer.h
        Client/include/Lobbies/Lobby.h

        Client/src/NetCommands/PickMapCommand.cpp
        Client/src/NetCommands/PickMapCommand.cpp
        Client/src/NetCommands/CommandDispatcher.cpp
        Client/src/NetCommands/LoadMapCommand.cpp
        Client/src/NetCommands/PlayerLoadedGameCommand.cpp
        Client/src/NetCommands/ClientCastSpellCommand.cpp
        Client/src/NetCommands/CreateLobbyCommand.cpp
        Client/src/NetCommands/JoinLobbyCommand.cpp
        Client/src/NetCommands/LeaveLobbyCommand.cpp
        Client/src/NetCommands/LogInCommand.cpp
        Client/src/NetCommands/NetCommand.cpp
        Client/src/NetCommands/ChatMessageCommand.cpp
        Client/src/NetCommands/PlayerIsReadyCommand.cpp
        Client/src/NetCommands/PickSpellCommand.cpp
        Client/src/NetCommands/ClientBuildTowerCommand.cpp

        Client/include/NetCommands/LoadMapCommand.h
        Client/include/NetCommands/ChatMessageCommand.h
        Client/include/NetCommands/PlayerLoadedGameCommand.h
        Client/include/NetCommands/PickSpellCommand.h
        Client/include/NetCommands/ClientCastSpellCommand.h
        Client/include/NetCommands/ClientBuildTowerCommand.h
        Client/include/NetCommands/CommandDispatcher.h
        Client/include/NetCommands/CreateLobbyCommand.h
        Client/include/NetCommands/JoinLobbyCommand.h
        Client/include/NetCommands/LeaveLobbyCommand.h
        Client/include/NetCommands/LogInCommand.h
        Client/include/NetCommands/NetCommand.h
        Client/include/NetCommands/PlayerIsReadyCommand.h

        Client/include/Exceptions/ClientDisconnectedException.h
        Client/include/Exceptions/OtherPlayerJoinedLobbyTwice.h
        Client/include/Exceptions/SomePlayerLeftLobbyAndLobbyNotSet.h
        Client/include/Exceptions/PlayerLeftTheLobbyAndWasntInIt.h

        Client/include/GTKNotifications/GTKNotification.h
        Client/src/GTKNotifications/GTKNotification.cpp
        Client/include/GTKNotifications/LogInSuccessGtkNotification.h
        Client/src/GTKNotifications/LogInSuccessGtkNotification.cpp
        Client/include/GTKNotifications/LogInFailedGtkNotification.h
        Client/src/GTKNotifications/LogInFailedGtkNotification.cpp

        Client/include/NonBlockingThreadSafeQueue.h
        Client/src/GTKNotifications/PlayerJoinedLobbyGTKNotification.cpp
        Client/include/GTKNotifications/PlayerJoinedLobbyGTKNotification.h)


set(SOURCE_FILES_EDITOR
        Client/View/Editor/AgregarEnemigoButton.cpp
        Client/View/Editor/AgregarEnemigoButton.h
        Client/View/Editor/EliminarEnemigoButton.cpp
        Client/View/Editor/EliminarEnemigoButton.h
        Client/View/Editor/EliminarHordaButton.cpp
        Client/View/Editor/EliminarHordaButton.h
        Client/View/Editor/NuevaHordaButton.cpp
        Client/View/Editor/NuevaHordaButton.h
        Client/View/Editor/SuperficieButton.cpp
        Client/View/Editor/SuperficieButton.h
        Client/View/Editor/EditorButtons.cpp
        Client/View/Editor/EditorButtons.h
        Client/View/Editor/Editor.cpp
        Client/View/Editor/Editor.h
        Client/View/Editor/ContadorEnemigosInput.cpp
        Client/View/Editor/ContadorEnemigosInput.h
        Client/View/Editor/AgregarCaminoButton.cpp
        Client/View/Editor/AgregarCaminoButton.h
        Client/View/Editor/AgregarTierraFirmeButton.cpp
        Client/View/Editor/AgregarTierraFirmeButton.h
        Client/View/Editor/AgregarPortalEntradaButton.cpp
        Client/View/Editor/AgregarPortalEntradaButton.h
        Client/View/Editor/AgregarPortalSalidaButton.cpp
        Client/View/Editor/AgregarPortalSalidaButton.h
        Client/View/Editor/Horda.cpp
        Client/View/Editor/Horda.h
        Client/View/Editor/EnemigoImage.cpp
        Client/View/Editor/EnemigoImage.h
        Client/View/Editor/EditorConstants.h
        Client/View/Editor/AumentarTiempoHordaButton.cpp
        Client/View/Editor/AumentarTiempoHordaButton.h
        Client/View/Editor/DisminuirTiempoHordaButton.cpp
        Client/View/Editor/DisminuirTiempoHordaButton.h
        Client/View/Editor/ContadorTiempoHordaInput.cpp
        Client/View/Editor/ContadorTiempoHordaInput.h
        Client/View/Editor/AumentarAnchoMapaButton.cpp
        Client/View/Editor/AumentarAnchoMapaButton.h
        Client/View/Editor/AumentarAltoMapaButton.cpp
        Client/View/Editor/AumentarAltoMapaButton.h
        Client/View/Editor/DisminuirAltoMapaButton.cpp
        Client/View/Editor/DisminuirAltoMapaButton.h
        Client/View/Editor/DisminuirAnchoMapaButton.cpp
        Client/View/Editor/DisminuirAnchoMapaButton.h
        Client/View/Editor/GuardarButton.cpp
        Client/View/Editor/GuardarButton.h
        Client/View/Editor/File.cpp
        Client/View/Editor/File.h
        Client/View/Common/Window.cpp
        Client/View/Common/Window.h
        Client/View/Common/ViewError.cpp
        Client/View/Common/ViewError.h
        Client/View/Common/Renderer.cpp
        Client/View/Common/Renderer.h
        Client/View/Common/TextureLoader.cpp
        Client/View/Common/TextureLoader.h
        Client/View/Common/Sprite.cpp
        Client/View/Common/Sprite.h
        Client/View/Common/SpriteNamesConfig.h
        Client/View/Common/View.cpp
        Client/View/Common/View.h
        Client/View/Common/MousePosition.cpp
        Client/View/Common/MousePosition.h
        Client/View/Common/Button.cpp
        Client/View/Common/Button.h
        Client/View/Common/Text.cpp
        Client/View/Common/Text.h
        Client/View/Common/Image.cpp
        Client/View/Common/Image.h
        Client/View/Common/AnimatedSprite.cpp
        Client/View/Common/AnimatedSprite.h
        Client/View/Model/MapView.cpp
        Client/View/Model/MapView.h
        Client/View/Model/PortalView.cpp
        Client/View/Model/PortalView.h
        Client/View/Model/PortalEntradaView.cpp
        Client/View/Model/PortalEntradaView.h
        Client/View/Model/PortalSalidaView.cpp
        Client/View/Model/PortalSalidaView.h
        Client/View/Editor/AumentarPaddingButton.cpp
        Client/View/Editor/AumentarPaddingButton.h
        Client/View/Editor/DisminuirPaddingButton.cpp
        Client/View/Editor/DisminuirPaddingButton.h
        Client/View/Editor/EditorValidationException.cpp
        Client/View/Editor/EditorValidationException.h
        Client/View/Editor/ContadorHordasInput.cpp
        Client/View/Editor/ContadorHordasInput.h
        Client/View/Common/MusicLoader.cpp
        Client/View/Common/MusicLoader.h
        Client/View/Common/MusicNamesConfig.h
        Client/View/Editor/AumentarTiempoEnemigosButton.cpp
        Client/View/Editor/AumentarTiempoEnemigosButton.h
        Client/View/Editor/DisminuirTiempoEnemigosButton.cpp
        Client/View/Editor/DisminuirTiempoEnemigosButton.h
        Client/View/Editor/ContadorTiempoEnemigosInput.cpp
        Client/View/Editor/ContadorTiempoEnemigosInput.h
        Client/View/Common/MouseMovement.cpp
        Client/View/Common/MouseMovement.h
        Client/View/Common/MusicPlayer.cpp
        Client/View/Common/MusicPlayer.h
        Client/View/Common/SoundEffect.cpp
        Client/View/Common/SoundEffect.h)


add_executable(TowerDefenseServer ${SOURCE_FILES_SERVER} Server/src/main.cpp)
add_executable(TowerDefenseEditor ${SOURCE_FILES_EDITOR} Client/View/mainEditor.cpp)
add_executable(TowerDefenseClient ${SOURCE_FILES_CLIENT} ${SOURCE_FILES_CLIENT_GTK} Client/main.cpp)
add_executable(TowerDefenseView ${SOURCE_FILES_CLIENT} ${SOURCE_FILES_CLIENT_GTK} Client/View/mainView.cpp)


INCLUDE(FindPkgConfig)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(TowerDefenseServer yaml-cpp)
target_link_libraries(TowerDefenseEditor yaml-cpp ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(TowerDefenseClient yaml-cpp X11 ${SDL2IMAGE_LIBRARIES} ${GTK3_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(TowerDefenseView yaml-cpp ${SDL2IMAGE_LIBRARIES} ${GTK3_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
