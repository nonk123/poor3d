cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(poor3d
    VERSION 0.1.0
    LANGUAGES C)

set(CMAKE_BUILD_SHARED_LIBRARIES OFF)

include(FetchContent)

FetchContent_Declare(poormans
    GIT_REPOSITORY https://github.com/nonk123/poormans.git
    GIT_TAG de96b8546a5fdf13be1b5ebeb9c7d3b6d2faaa25)

FetchContent_Declare(S_tructures
    GIT_REPOSITORY https://github.com/Schwungus/S_tructures.git
    GIT_TAG 2bb14085172b06afeca00783c7b4f30fe3210b68)

FetchContent_MakeAvailable(poormans S_tructures)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE poormans S_tructures)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . COMPONENT ${PROJECT_NAME})
install(FILES README.md UNLICENSE $<TARGET_FILE:${PROJECT_NAME}>
    DESTINATION . COMPONENT ${PROJECT_NAME})
install(DIRECTORY assets DESTINATION . COMPONENT ${PROJECT_NAME})

set(CPACK_GENERATOR ZIP)
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
set(CPACK_COMPONENTS_ALL ${PROJECT_NAME})
include(CPack)
