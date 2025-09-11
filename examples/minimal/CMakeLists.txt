cmake_minimum_required(VERSION 3.29)

set(SOURCES
    main.cpp)

set(HEADERS)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_executable(Scorpion-minimal ${SOURCES} ${HEADERS})

target_link_libraries(Scorpion-minimal PUBLIC Scorpion)

target_compile_features(Scorpion-minimal PUBLIC c_std_17 cxx_std_20)

set_target_properties(Scorpion-minimal PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF

    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(WIN32)
    add_custom_command(TARGET Scorpion-minimal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Scorpion>
        $<TARGET_FILE_DIR:Scorpion-minimal>
    )
endif()