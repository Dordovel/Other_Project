cmake_minimum_required(VERSION 3.15)
project(SFMLProject_rebuild)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -g")

#set(CMAKE_CXX_CLANG_TIDY clang-tidy-10 -checks=-*,readability-avoid-const-params-in-decls,readability-const-return-type,readability-container-size-empty,readability-convert-member-functions-to-static,readability-delete-null-pointer,readability-deleted-default,readability-else-after-return,readability-function-size,readability-identifier-naming,readability-implicit-bool-conversion,readability-inconsistent-declaration-parameter-name,readability-isolate-declaration,readability-magic-numbers,readability-make-member-function-const,readability-misleading-indentation,readability-misplaced-array-index,readability-named-parameter,readability-non-const-parameter,readability-qualified-auto,readability-redundant-access-specifiers,readability-redundant-control-flow,readability-redundant-declaration,readability-redundant-function-ptr-dereference,readability-redundant-member-init,readability-redundant-preprocessor,readability-redundant-smartptr-get,readability-redundant-string-cstr,readability-redundant-string-init,readability-simplify-boolean-expr,readability-simplify-subscript-expr,readability-static-accessed-through-instance,readability-static-definition-in-anonymous-namespace,readability-string-compare,readability-uniqueptr-delete-release,readability-uppercase-literal-suffix,readability-use-anyofallof)



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
              Game_Resources/map_loader/include/box2d/b2_block_allocator.h
        Game_Resources/map_loader/include/box2d/b2_body.h
        Game_Resources/map_loader/include/box2d/b2_broad_phase.h
        Game_Resources/map_loader/include/box2d/b2_chain_shape.h
        Game_Resources/map_loader/include/box2d/b2_circle_shape.h
        Game_Resources/map_loader/include/box2d/b2_collision.h
        Game_Resources/map_loader/include/box2d/b2_contact.h
        Game_Resources/map_loader/include/box2d/b2_contact_manager.h
        Game_Resources/map_loader/include/box2d/b2_distance.h
        Game_Resources/map_loader/include/box2d/b2_distance_joint.h
        Game_Resources/map_loader/include/box2d/b2_draw.h
        Game_Resources/map_loader/include/box2d/b2_dynamic_tree.h
        Game_Resources/map_loader/include/box2d/b2_edge_shape.h
        Game_Resources/map_loader/include/box2d/b2_fixture.h
        Game_Resources/map_loader/include/box2d/b2_friction_joint.h
        Game_Resources/map_loader/include/box2d/b2_gear_joint.h
        Game_Resources/map_loader/include/box2d/b2_growable_stack.h
        Game_Resources/map_loader/include/box2d/b2_joint.h
        Game_Resources/map_loader/include/box2d/b2_math.h
        Game_Resources/map_loader/include/box2d/b2_motor_joint.h
        Game_Resources/map_loader/include/box2d/b2_mouse_joint.h
        Game_Resources/map_loader/include/box2d/b2_polygon_shape.h
        Game_Resources/map_loader/include/box2d/b2_prismatic_joint.h
        Game_Resources/map_loader/include/box2d/b2_pulley_joint.h
        Game_Resources/map_loader/include/box2d/b2_revolute_joint.h
        Game_Resources/map_loader/include/box2d/b2_rope.h
        Game_Resources/map_loader/include/box2d/b2_rope_joint.h
        Game_Resources/map_loader/include/box2d/b2_settings.h
        Game_Resources/map_loader/include/box2d/b2_shape.h
        Game_Resources/map_loader/include/box2d/b2_stack_allocator.h
        Game_Resources/map_loader/include/box2d/b2_time_of_impact.h
        Game_Resources/map_loader/include/box2d/b2_time_step.h
        Game_Resources/map_loader/include/box2d/b2_timer.h
        Game_Resources/map_loader/include/box2d/b2_weld_joint.h
        Game_Resources/map_loader/include/box2d/b2_wheel_joint.h
        Game_Resources/map_loader/include/box2d/b2_world.h
        Game_Resources/map_loader/include/box2d/b2_world_callbacks.h
        Game_Resources/map_loader/include/box2d/box2d.h
        Game_Resources/map_loader/include/collision/b2_broad_phase.cpp
        Game_Resources/map_loader/include/collision/b2_chain_shape.cpp
        Game_Resources/map_loader/include/collision/b2_circle_shape.cpp
        Game_Resources/map_loader/include/collision/b2_collide_circle.cpp
        Game_Resources/map_loader/include/collision/b2_collide_edge.cpp
        Game_Resources/map_loader/include/collision/b2_collide_polygon.cpp
        Game_Resources/map_loader/include/collision/b2_collision.cpp
        Game_Resources/map_loader/include/collision/b2_distance.cpp
        Game_Resources/map_loader/include/collision/b2_dynamic_tree.cpp
        Game_Resources/map_loader/include/collision/b2_edge_shape.cpp
        Game_Resources/map_loader/include/collision/b2_polygon_shape.cpp
        Game_Resources/map_loader/include/collision/b2_time_of_impact.cpp
        Game_Resources/map_loader/include/common/b2_block_allocator.cpp
        Game_Resources/map_loader/include/common/b2_draw.cpp
        Game_Resources/map_loader/include/common/b2_math.cpp
        Game_Resources/map_loader/include/common/b2_settings.cpp
        Game_Resources/map_loader/include/common/b2_stack_allocator.cpp
        Game_Resources/map_loader/include/common/b2_timer.cpp
        Game_Resources/map_loader/include/dynamics/b2_body.cpp
        Game_Resources/map_loader/include/dynamics/b2_chain_circle_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_chain_circle_contact.h
        Game_Resources/map_loader/include/dynamics/b2_chain_polygon_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_chain_polygon_contact.h
        Game_Resources/map_loader/include/dynamics/b2_circle_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_circle_contact.h
        Game_Resources/map_loader/include/dynamics/b2_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_contact_manager.cpp
        Game_Resources/map_loader/include/dynamics/b2_contact_solver.cpp
        Game_Resources/map_loader/include/dynamics/b2_contact_solver.h
        Game_Resources/map_loader/include/dynamics/b2_distance_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_edge_circle_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_edge_circle_contact.h
        Game_Resources/map_loader/include/dynamics/b2_edge_polygon_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_edge_polygon_contact.h
        Game_Resources/map_loader/include/dynamics/b2_fixture.cpp
        Game_Resources/map_loader/include/dynamics/b2_friction_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_gear_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_island.cpp
        Game_Resources/map_loader/include/dynamics/b2_island.h
        Game_Resources/map_loader/include/dynamics/b2_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_motor_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_mouse_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_polygon_circle_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_polygon_circle_contact.h
        Game_Resources/map_loader/include/dynamics/b2_polygon_contact.cpp
        Game_Resources/map_loader/include/dynamics/b2_polygon_contact.h
        Game_Resources/map_loader/include/dynamics/b2_prismatic_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_pulley_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_revolute_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_rope_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_weld_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_wheel_joint.cpp
        Game_Resources/map_loader/include/dynamics/b2_world.cpp
        Game_Resources/map_loader/include/dynamics/b2_world_callbacks.cpp
        Game_Resources/map_loader/include/pugixml/pugiconfig.hpp
        Game_Resources/map_loader/include/pugixml/pugixml.hpp
        Game_Resources/map_loader/include/rope/b2_rope.cpp
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
		${CMAKE_SOURCE_DIR}/struct/collectionobject.cpp
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
