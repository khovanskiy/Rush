cmake_minimum_required(VERSION 3.4)
IF(${CMAKE_IS_SERVER})
    message("Generate makefile for SERVER")
    set(PROJECT Server)
ELSE()
    message("Generate makefile for CLIENT")
    set(PROJECT Client)
ENDIF()
project(${PROJECT})

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5OpenGL REQUIRED)

IF(${CMAKE_IS_SERVER})
    set(SOURCE_FILES server-main.cpp)
ELSE()
    set(SOURCE_FILES client/main.cpp)
    file(COPY ./DATA DESTINATION .)
ENDIF()
set(SOURCE_FILES
        ${SOURCE_FILES}
        api.cpp
        api.h
        client/background.cpp
        client/background.h
        client/bitmap.cpp
        client/bitmap.h
        common/bullet.cpp
        common/bullet.h
        client/bulletview.cpp
        client/bulletview.h
        client/camera.cpp
        client/camera.h
        client/cameracontroller.cpp
        client/cameracontroller.h
        common/carwheel.cpp
        common/carwheel.h
        common/chassis.cpp
        common/chassis.h
        common/console.h
        client/displayobject.cpp
        client/displayobject.h
        client/displayobjectcontainer.cpp
        client/displayobjectcontainer.h
        common/event.cpp
        common/event.h
        common/eventdispatcher.cpp
        common/eventdispatcher.h
        common/eventhandler.h
        common/exception.cpp
        common/exception.h
        client/exitstate.cpp
        client/exitstate.h
        common/explosion.cpp
        common/explosion.h
        common/gamemodelobject.cpp
        common/gamemodelobject.h
        gameobjectevent.cpp
        gameobjectevent.h
        client/gameplaystate.cpp
        client/gameplaystate.h
        client/gameviewobject.cpp
        client/gameviewobject.h
        gameworld.cpp
        gameworld.h
        common/geometry2d.cpp
        common/geometry2d.h
        client/graphiccore.cpp
        client/graphiccore.h
        idsystem.cpp
        idsystem.h
        client/initstate.cpp
        client/initstate.h
        client/interactiveobject.cpp
        client/interactiveobject.h
        client/interface.cpp
        client/interface.h
        client/keyboard.cpp
        client/keyboard.h
        client/keyboardevent.cpp
        client/keyboardevent.h
        client/mainmenustate.cpp
        client/mainmenustate.h
        client/mapview.cpp
        client/mapview.h
        common/matrix.cpp
        common/matrix.h
        client/mouse.cpp
        client/mouse.h
        client/mouseevent.cpp
        client/mouseevent.h
        client/movieclip.cpp
        client/movieclip.h
        networkclient.cpp
        networkclient.h
        networkevent.cpp
        networkevent.h
        networkobject.cpp
        networkobject.h
        networkserver.cpp
        networkserver.h
        common/obstacle.cpp
        common/obstacle.h
        client/obstacleview.cpp
        client/obstacleview.h
        common/physicsobject.cpp
        common/physicsobject.h
        common/physicsobjectfactory.cpp
        common/physicsobjectfactory.h
        common/physicssystem.cpp
        common/physicssystem.h
        common/physicsworld.cpp
        common/physicsworld.h
        client/program.cpp
        client/program.h
        common/protocol.cpp
        common/protocol.h
        common/random.cpp
        common/random.h
        README.md
        renderdata.cpp
        renderdata.h
        server.cpp
        server.h
        serverstate.cpp
        serverstate.h
        client/sprite.cpp
        client/sprite.h
        client/stage.cpp
        client/stage.h
        common/state.cpp
        common/state.h
        common/statecontext.cpp
        common/statecontext.h
        common/stateevent.cpp
        common/stateevent.h
        client/statefactory.cpp
        client/statefactory.h
        common/terrain.cpp
        common/terrain.h
        client/terrainview.cpp
        client/terrainview.h
        common/track.cpp
        common/track.h
        common/transformableobject.cpp
        common/transformableobject.h
        common/turret.cpp
        common/turret.h
        client/turretview.cpp
        client/turretview.h
        client/uivehiclecontroller.cpp
        client/uivehiclecontroller.h
        common/vector2d.cpp
        common/vector2d.h
        common/vehicle.cpp
        common/vehicle.h
        common/vehiclebody.cpp
        common/vehiclebody.h
        common/vehicleengine.cpp
        common/vehicleengine.h
        client/vehicleview.cpp
        client/vehicleview.h
        client/view.cpp
        client/view.h
        common/wheel.cpp
        common/wheel.h
        common/WheelState.h
        common/AccelerationState.h
        common/GameObjectType.h
        common/StateEnum.h
        multicastparams.h
        multicastparams.cpp
        common/Arguments.cpp common/Arguments.h)

add_executable(${PROJECT} ${SOURCE_FILES})

#target_link_libraries(Rush Qt5::Core)
#target_link_libraries(Rush Qt5::Gui)
#target_link_libraries(Rush Qt5::Widgets)
#target_link_libraries(Rush Qt5::Network)
qt5_use_modules(${PROJECT} Core Widgets Gui Network Multimedia OpenGL)

if( WIN32 )
    target_link_libraries(${PROJECT} OpenGL32)
else()
    target_link_libraries(${PROJECT} GL)
endif()
