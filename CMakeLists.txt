cmake_minimum_required(VERSION 3.10)
project(some_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)

include_directories(
    ${EIGEN3_INCLUDE_DIR} 
    ${PROJECT_SOURCE_DIR}/include 
    ${PROJECT_SOURCE_DIR}/utils 
    ${Boost_INCLUDE_DIRS} 
    ${GLFW_INCLUDE_DIRS} 
    ${OpenCV_INCLUDE_DIRS} 
    ${OpenGL_INCLUDE_DIRS}
)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(utils SHARED utils/trans.cpp utils/logger.cpp)
target_link_libraries(utils PUBLIC ${Eigen3_LIBRARIES} spdlog::spdlog)

add_library(viewer SHARED include/gviewer.cpp include/visualization.cpp)
target_link_libraries(viewer PUBLIC ${OpenCV_LIBRARIES} ${OPENGL_LIBRARIES} glfw utils)

add_executable(main src/main.cpp)
target_link_libraries(main viewer)

add_executable(fit src/fit.cpp)
target_link_libraries(fit viewer)
