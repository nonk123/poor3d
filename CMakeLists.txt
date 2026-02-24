cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(poor3d LANGUAGES C)

set(CMAKE_BUILD_SHARED_LIBRARIES OFF)

include(FetchContent)

FetchContent_Declare(poormans
    GIT_REPOSITORY https://github.com/nonk123/poormans.git
    GIT_TAG 5cfff2a46c7f7fe8b9a80819d3f3e526d66e9ac5)

FetchContent_Declare(S_tructures
    GIT_REPOSITORY https://github.com/Schwungus/S_tructures.git
    GIT_TAG 2bb14085172b06afeca00783c7b4f30fe3210b68)

FetchContent_MakeAvailable(poormans S_tructures)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE poormans S_tructures)
