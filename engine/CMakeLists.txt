cmake_minimum_required(VERSION 3.29)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

set(SOURCES
    src/core/scorpion.cpp
    src/render/renderer.cpp
    src/foundation/memory/allocator.c
        src/core/actor.cpp
        src/core/scene.cpp
    src/engine_std/transform.cpp
    src/engine_std/camera.cpp
    src/engine_std/cube_renderer.cpp
    src/util/actor_factory.cpp
    src/core/component.cpp)

set(HEADERS
    include/scorpion/core/scorpion.h
    include/scorpion/core/api.h
    include/scorpion/util/timer.h
    include/scorpion/render/renderer.h
    include/scorpion/foundation/memory/allocator.h
        include/scorpion/core/actor.h
        include/scorpion/core/component.h
        include/scorpion/util/std_types.h
        include/scorpion/core/scene.h
        include/scorpion/engine_std/transform.h
        include/scorpion/util/math.h
    include/scorpion/util/lazy.h
    include/scorpion/engine_std/camera.h
    include/scorpion/engine_std/cube_renderer.h
    include/scorpion/util/actor_factory.h)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(Scorpion SHARED ${SOURCES} ${HEADERS})

target_include_directories(Scorpion
    PUBLIC
        include
)

target_link_libraries(Scorpion PUBLIC raylib)

target_compile_features(Scorpion PUBLIC c_std_17 cxx_std_20)

set_target_properties(Scorpion PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF

    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_compile_definitions(Scorpion PRIVATE SCORPION_BUILD)

if(WIN32)
    target_compile_definitions(Scorpion PUBLIC PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(Scorpion PUBLIC PLATFORM_MACOS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(Scorpion PUBLIC PLATFORM_LINUX)
endif()