cmake_minimum_required(VERSION 3.15)
project(SFMLProject_rebuild)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Game_Resources/map_loader/include)
include_directories(Game_Resources/map_loader/include/Box2D)
include_directories(Game_Resources/map_loader/include/Box2D/Collision)
include_directories(Game_Resources/map_loader/include/Box2D/Collision/Shapes)
include_directories(Game_Resources/map_loader/include/Box2D/Common)
include_directories(Game_Resources/map_loader/include/Box2D/Dynamics)
include_directories(Game_Resources/map_loader/include/Box2D/Dynamics/Contacts)
include_directories(Game_Resources/map_loader/include/Box2D/Dynamics/Joints)
include_directories(Game_Resources/map_loader/include/Box2D/Rope)
include_directories(Game_Resources/map_loader/include/pugixml)
include_directories(Game_Resources/map_loader/include/tmx)
include_directories(Game_Resources/map_loader/MapLoader)
include_directories(headers)
include_directories(Interface)
include_directories(struct)

file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB SOURCE_FILES_ALGORITHM ${CMAKE_SOURCE_DIR}/algorithm/*.cpp)
file(GLOB SOURCE_FILES_OBJECT ${CMAKE_SOURCE_DIR}/graphicobject/*.cpp)

add_executable(SFMLProject_rebuild
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2ChainShape.cpp
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2ChainShape.h
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2CircleShape.cpp
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2CircleShape.h
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2EdgeShape.cpp
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2EdgeShape.h
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2PolygonShape.cpp
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2PolygonShape.h
        Game_Resources/map_loader/include/Box2D/Collision/Shapes/b2Shape.h
        Game_Resources/map_loader/include/Box2D/Collision/b2BroadPhase.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2BroadPhase.h
        Game_Resources/map_loader/include/Box2D/Collision/b2CollideCircle.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2CollideEdge.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2CollidePolygon.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2Collision.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2Collision.h
        Game_Resources/map_loader/include/Box2D/Collision/b2Distance.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2Distance.h
        Game_Resources/map_loader/include/Box2D/Collision/b2DynamicTree.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2DynamicTree.h
        Game_Resources/map_loader/include/Box2D/Collision/b2TimeOfImpact.cpp
        Game_Resources/map_loader/include/Box2D/Collision/b2TimeOfImpact.h
        Game_Resources/map_loader/include/Box2D/Common/b2BlockAllocator.cpp
        Game_Resources/map_loader/include/Box2D/Common/b2BlockAllocator.h
        Game_Resources/map_loader/include/Box2D/Common/b2Draw.cpp
        Game_Resources/map_loader/include/Box2D/Common/b2Draw.h
        Game_Resources/map_loader/include/Box2D/Common/b2GrowableStack.h
        Game_Resources/map_loader/include/Box2D/Common/b2Math.cpp
        Game_Resources/map_loader/include/Box2D/Common/b2Math.h
        Game_Resources/map_loader/include/Box2D/Common/b2Settings.cpp
        Game_Resources/map_loader/include/Box2D/Common/b2Settings.h
        Game_Resources/map_loader/include/Box2D/Common/b2StackAllocator.cpp
        Game_Resources/map_loader/include/Box2D/Common/b2StackAllocator.h
        Game_Resources/map_loader/include/Box2D/Common/b2Timer.cpp
        Game_Resources/map_loader/include/Box2D/Common/b2Timer.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2CircleContact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2CircleContact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2Contact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2Contact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2ContactSolver.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Contacts/b2PolygonContact.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2DistanceJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2FrictionJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2GearJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2GearJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2Joint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2Joint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2MotorJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2MotorJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2MouseJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2MouseJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2PrismaticJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2PulleyJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2RevoluteJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2RopeJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2RopeJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2WeldJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2WeldJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2WheelJoint.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/Joints/b2WheelJoint.h
        Game_Resources/map_loader/include/Box2D/Dynamics/b2Body.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/b2Body.h
        Game_Resources/map_loader/include/Box2D/Dynamics/b2ContactManager.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/b2ContactManager.h
        Game_Resources/map_loader/include/Box2D/Dynamics/b2Fixture.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/b2Fixture.h
        Game_Resources/map_loader/include/Box2D/Dynamics/b2Island.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/b2Island.h
        Game_Resources/map_loader/include/Box2D/Dynamics/b2TimeStep.h
        Game_Resources/map_loader/include/Box2D/Dynamics/b2World.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/b2World.h
        Game_Resources/map_loader/include/Box2D/Dynamics/b2WorldCallbacks.cpp
        Game_Resources/map_loader/include/Box2D/Dynamics/b2WorldCallbacks.h
        Game_Resources/map_loader/include/Box2D/Rope/b2Rope.cpp
        Game_Resources/map_loader/include/Box2D/Rope/b2Rope.h
        Game_Resources/map_loader/include/Box2D/Box2D.h
        Game_Resources/map_loader/include/pugixml/pugiconfig.hpp
        Game_Resources/map_loader/include/pugixml/pugixml.hpp
        Game_Resources/map_loader/include/tmx/DebugShape.hpp
        Game_Resources/map_loader/include/tmx/Export.hpp
        Game_Resources/map_loader/include/tmx/Helpers.hpp
        Game_Resources/map_loader/include/tmx/Log.hpp
        Game_Resources/map_loader/include/tmx/MapLayer.hpp
        Game_Resources/map_loader/include/tmx/MapLoader.hpp
        Game_Resources/map_loader/include/tmx/MapObject.hpp
        Game_Resources/map_loader/include/tmx/QuadTreeNode.hpp
        Game_Resources/map_loader/include/tmx/tmx2box2d.hpp
        Game_Resources/map_loader/MapLoader/pugixml/pugixml.cpp
        Game_Resources/map_loader/MapLoader/DebugShape.cpp
        Game_Resources/map_loader/MapLoader/Log.cpp
        Game_Resources/map_loader/MapLoader/MapLayer.cpp
        Game_Resources/map_loader/MapLoader/MapLoaderPrivate.cpp
        Game_Resources/map_loader/MapLoader/MapLoaderPublic.cpp
        Game_Resources/map_loader/MapLoader/MapObject.cpp
        Game_Resources/map_loader/MapLoader/miniz.c
        Game_Resources/map_loader/MapLoader/miniz.h
        Game_Resources/map_loader/MapLoader/QuadTreeNode.cpp
        Game_Resources/map_loader/MapLoader/tmx2box2d.cpp
        ${SOURCE_FILES}
        ${SOURCE_FILES_ALGORITHM}
        ${SOURCE_FILES_OBJECT}
        main.cpp)

if (UNIX)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/Game_Resources/SFML-2.5.1/unix)
endif (UNIX)

if(WIN32)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/Game_Resources/SFML-2.5.1/win)
endif(WIN32)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio -ggdb)
endif()

find_package(Threads)
if (THREADS_FOUND)
    message("Threads Found")
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()