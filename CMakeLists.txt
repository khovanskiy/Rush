cmake_minimum_required(VERSION 3.4)
set(PROJECT Server)
project(${PROJECT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5OpenGL REQUIRED)

set(SOURCE_FILES
        server-main.cpp
        #main.cpp
        api.cpp
        api.h
        background.cpp
        background.h
        client/bitmap.cpp
        client/bitmap.h
        bullet.cpp
        bullet.h
        bulletfactory.cpp
        bulletview.cpp
        bulletview.h
        camera.cpp
        camera.h
        cameracontroller.cpp
        cameracontroller.h
        carwheel.cpp
        carwheel.h
        chassis.cpp
        chassis.h
        console.cpp
        console.h
        displayobject.cpp
        displayobject.h
        displayobjectcontainer.cpp
        displayobjectcontainer.h
        event.cpp
        event.h
        eventdispatcher.cpp
        eventdispatcher.h
        eventhandler.h
        exception.cpp
        exception.h
        exitstate.cpp
        exitstate.h
        explosion.cpp
        explosion.h
        gamemodelobject.cpp
        gamemodelobject.h
        gameobjectevent.cpp
        gameobjectevent.h
        gameplaystate.cpp
        gameplaystate.h
        gameviewobject.cpp
        gameviewobject.h
        gameworld.cpp
        gameworld.h
        geometry2d.cpp
        geometry2d.h
        graphiccore.cpp
        graphiccore.h
        idsystem.cpp
        idsystem.h
        initstate.cpp
        initstate.h
        interactiveobject.cpp
        interactiveobject.h
        interface.cpp
        interface.h
        keyboard.cpp
        keyboard.h
        keyboardevent.cpp
        keyboardevent.h
        loader.cpp
        loader.h
        mainmenustate.cpp
        mainmenustate.h
        mapview.cpp
        mapview.h
        matrix.cpp
        matrix.h
        mouse.cpp
        mouse.h
        mouseevent.cpp
        mouseevent.h
        movieclip.cpp
        movieclip.h
        networkclient.cpp
        networkclient.h
        networkevent.cpp
        networkevent.h
        networkobject.cpp
        networkobject.h
        networkserver.cpp
        networkserver.h
        obstacle.cpp
        obstacle.h
        obstacleview.cpp
        obstacleview.h
        physicsobject.cpp
        physicsobject.h
        physicsobjectfactory.cpp
        physicsobjectfactory.h
        physicssystem.cpp
        physicssystem.h
        physicsworld.cpp
        physicsworld.h
        program.cpp
        program.h
        protocol.cpp
        protocol.h
        random.cpp
        random.h
        README.md
        renderdata.cpp
        renderdata.h
        sampleview.cpp
        sampleview.h
        server.cpp
        server.h
        serverstate.cpp
        serverstate.h
        sprite.cpp
        sprite.h
        stage.cpp
        stage.h
        state.cpp
        state.h
        statecontext.cpp
        statecontext.h
        stateevent.cpp
        stateevent.h
        statefactory.cpp
        statefactory.h
        terrain.cpp
        terrain.h
        terrainview.cpp
        terrainview.h
        #thread.cpp
        #thread.h
        track.cpp
        track.h
        transformableobject.cpp
        transformableobject.h
        turret.cpp
        turret.h
        turretview.cpp
        turretview.h
        uivehiclecontroller.cpp
        uivehiclecontroller.h
        vector2d.cpp
        vector2d.h
        vehicle.cpp
        vehicle.h
        vehiclebody.cpp
        vehiclebody.h
        vehicleengine.cpp
        vehicleengine.h
        vehicleview.cpp
        vehicleview.h
        view.cpp
        view.h
        common/wheel.cpp
        common/wheel.h
        common/WheelState.h
        common/AccelerationState.h
        common/GameObjectType.h
        common/StateEnum.h)

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
