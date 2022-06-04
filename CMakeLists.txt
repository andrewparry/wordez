cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

project(wordez)

find_package(wxWidgets REQUIRED COMPONENTS core base adv gl)
include(${wxWidgets_USE_FILE})

file(GLOB project_SRCS src/*.cpp)

add_executable(wordez ${project_SRCS})
target_link_libraries(wordez ${wxWidgets_LIBRARIES})
target_include_directories(wordez PRIVATE ${wxWidgets_INCLUDE_DIRS})
