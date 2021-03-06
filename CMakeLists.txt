# Run cmake . to build Makefile

cmake_minimum_required(VERSION 2.6)

# Project name
project(Modal)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

SET(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable")

# Make some sets of files

file(
    GLOB_RECURSE
    core_sources
    src/core/*
)

file(
    GLOB_RECURSE
    net_sources
    src/net/*
)

file(
    GLOB_RECURSE
    parser_sources
    src/parser/*
)

file(
    GLOB_RECURSE
    tun_sources
    src/tuntap/*
)

file(
    GLOB_RECURSE
    route_sources
    src/modRoute/*
)

file(
    GLOB_RECURSE
    wlan_sources
    src/wlan0/*
)

file(
    GLOB_RECURSE
    linking_sources
    src/linking/*
    )
# Test executables

add_executable(
    test-tuntap
    ${core_sources}
    ${net_sources}
    ${parser_sources}
    ${tun_sources}
    src/test-tuninterface.cpp
)
target_link_libraries(
    test-tuntap
    pthread
    )

add_executable(
    test-wlan0
    ${core_sources}
    ${net_sources}
    ${parser_sources}
    ${wlan_sources}
    ${linking_sources}
    ${tun_sources}
    ${route_sources}
    src/wlan-test.cpp
)
target_link_libraries(
    test-wlan0
    pthread
)

add_executable(
    demo
    ${core_sources}
    ${net_sources}
    ${parser_sources}
    ${wlan_sources}
    ${linking_sources}
    ${tun_sources}
    ${route_sources}
    src/appli.cpp
)
target_link_libraries(
    demo
    pthread
)
