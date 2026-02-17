cmake_minimum_required(VERSION 3.31)

project(app
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Helpful defaults
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


include(CTest)  # enables testing infrastructure

# ---- Qt6 ----
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB_RECURSE APP_SOURCES 
    src/*.cpp
    include/*.hpp
    resources/*.qrc
)

add_executable(app ${APP_SOURCES})

target_link_libraries(app PRIVATE Qt6::Core Qt6::Widgets ZasLib::Core)
target_include_directories(app PRIVATE include)

# ---- Catch2 ----
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

# ---- ZasLib ----
FetchContent_Declare(
  ZasLib
  GIT_REPOSITORY git@github.com:jacobg431/zombie-apocalypse-survivors-library.git
  GIT_TAG        main
)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(ZasLib)
set(BUILD_TESTING ON CACHE BOOL "" FORCE)

if(BUILD_TESTING)
  add_executable(tests
    tests/test.cpp
  )
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Qt6::Core Qt6::Widgets ZasLib::Core)

  add_test(NAME unit_tests COMMAND tests)
endif()
