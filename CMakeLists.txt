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
)

add_executable(app ${APP_SOURCES})

target_link_libraries(app PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(app PRIVATE include)

# ---- Catch2 ----
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)


if(BUILD_TESTING)
  add_executable(tests
    tests/test.cpp
  )
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

  add_test(NAME unit_tests COMMAND tests)
endif()
