cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Json)
add_library(
  ${PROJECT_NAME}
  STATIC
  ../sources/Json.cpp
  ../sources/JsonParser.cpp
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ../include
)

 set(MAIN_NAME ${PROJECT_NAME}Main)

  add_executable(
    ${MAIN_NAME}
    ../sources/main.cpp)

  target_include_directories(
    ${MAIN_NAME}
    PUBLIC ../include)

  target_link_libraries(${MAIN_NAME} ${PROJECT_NAME})
