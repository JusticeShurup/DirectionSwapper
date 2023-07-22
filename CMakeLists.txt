cmake_minimum_required(VERSION 3.26.4)

set(PROJECT_NAME DirectionSwapper)
set(EXECUTABLE_NAME main)
set(OpenCV_DIR "C://OpenCV-MinGW-Build-OpenCV-4.5.5-x64")
project(${PROJECT_NAME} LANGUAGES CXX)


file(GLOB SOURCES "src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(${EXECUTABLE_NAME} ${SOURCES})
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${OpenCV_LIBS})
endif()
