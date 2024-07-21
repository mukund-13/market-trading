cmake_minimum_required(VERSION 3.10)
project(TradingSystem)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

add_executable(TradingSystem ${SOURCES})

# Add any required libraries
find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(TradingSystem ${Boost_LIBRARIES})
endif()
