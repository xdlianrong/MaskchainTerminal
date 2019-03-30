cmake_minimum_required(VERSION 2.8)

project(MaskashTerminal)

find_package(Boost REQUIRED COMPONENTS program_options)
if(NOT Boost_FOUND)
    message("Not found Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

add_compile_options(-std=c++11 -g)

add_executable(MaskashTerminal terminal.cpp)

target_link_libraries(MaskashTerminal ${Boost_LIBRARIES} pthread boost_system)


