cmake_minimum_required(VERSION 3.10)
project(some_project)

set(LIBRARY_NAME some_project_lib)

set(CMAKE_CXX_STANDARD 11)

################################################################################
# Dependencies
################################################################################

################################################################################
# Sources
################################################################################

set(root ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADER_FILES
        ${root}/src/package_1/simple.h
)

set(SOURCE_FILES
        ${root}/src/package_1/simple.cpp
)

# Organize the source and header files into groups
source_group("Headers" FILES ${HEADER_FILES})
source_group("Source" FILES ${SOURCE_FILES})

if(CMAKE_VERSION VERSION_GREATER 3.8)
    source_group(TREE ${root} FILES ${HEADER_FILES} ${SOURCE_FILES})
endif()

################################################################################
# Build
################################################################################

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(${LIBRARY_NAME} SHARED
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries(${LIBRARY_NAME}
)

################################################################################
# Executables
################################################################################

add_executable(some_project_bin src/main.cpp)
target_link_libraries(some_project_bin
        PUBLIC
            ${LIBRARY_NAME}
        )
