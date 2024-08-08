cmake_minimum_required(VERSION 3.8)
project(Test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

find_package(glfw3 REQUIRED) 
find_package(OpenGL REQUIRED)
find_package(spdlog REQUIRED)
find_package(eigen3 REQUIRED)
find_package(OpenCV 3 REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/utils
    ${GLFW_INCLUDE_DIR}
    ${OpenGL_INCLUDE_DIR}
    ${SPDLOG_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
add_library(utils SHARED utils/logger.cpp utils/transfer.cpp)
target_link_libraries(utils PUBLIC spdlog::spdlog ${Eigen3_LIBRARIES} glfw ${OPENGL_LIBRARIES})

add_executable(main src/main.cpp)
target_link_libraries(main utils)
