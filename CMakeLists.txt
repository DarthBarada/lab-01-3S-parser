cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)
option(BUILD_DEMO "Build 2nd task (demo app)" OFF)
option(BUILD_BROKER "Build 3rd task (broker)" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
  SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(Json)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(
  ${PROJECT_NAME}
  STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Json.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/JsonParser.cpp
)

add_executable(
  tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/JsonTest_1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/JsonTest_2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/JsonTest_3.cpp
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(
  tests
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${GTEST_ROOT}/include
)
find_library(
  GTEST_LOCAL_LIB
  NAMES gtest
  PATHS ${PROJECT_NAME}/lib64/
)
find_library(
  GTEST_LOCAL_LIB_MAIN
  NAMES gtest_main
  PATHS ${PROJECT_NAME}/lib64/
)
target_link_libraries(
  tests
  ${CMAKE_THREAD_LIBS_INIT}
  ${GTEST_LOCAL_LIB}
  ${GTEST_LOCAL_LIB_MAIN}
  ${PROJECT_NAME}
)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

if (BUILD_DEMO)
  set(DEMO_NAME ${PROJECT_NAME}Demo)
  add_executable(
    ${DEMO_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
  )

  target_include_directories(
    ${DEMO_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(${DEMO_NAME} ${PROJECT_NAME})
endif ()

if (BUILD_BROKER)
  hunter_add_package(nlohmann_json)
  find_package(nlohmann_json CONFIG REQUIRED)

  set(BROKER_NAME ${PROJECT_NAME}Broker)
  add_executable(
    ${BROKER_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/broker/main.cpp
  )

  target_include_directories(
    ${BROKER_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(${BROKER_NAME} ${PROJECT_NAME} nlohmann_json::nlohmann_json)
endif ()

if (BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  add_coverage(${PROJECT_NAME})
  add_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif ()

