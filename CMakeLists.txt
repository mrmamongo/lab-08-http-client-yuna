cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

# set(
#   HUNTER_CACHE_SERVERS
#   "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
#   CACHE STRING "Default cache server"
# )

# include("cmake/HunterGate.cmake")

# HunterGate(
#   URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
#   SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
# )

# TODO: rename project and delete this comment
project(http_client VERSION 0.1.0)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")


set(Boost_INCLUDE_DIR /home/lamp/boost_1_75_0)
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost COMPONENTS system thread filesystem log program_options date_time REQUIRED)

add_subdirectory(third-party/json)

find_package(Threads)

set(Boost_L Boost::log Boost::log_setup Boost::thread Boost::system Boost::filesystem Boost::date_time)

add_executable(${PROJECT_NAME} sources/client_exampel.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_L} Boost::headers nlohmann_json::nlohmann_json)

include(CPackConfig.cmake)

install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}-targets"
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

install(EXPORT "${PROJECT_NAME}-targets"
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION "lib/cmake"
)
