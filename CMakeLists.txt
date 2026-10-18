cmake_minimum_required(VERSION 3.25)
project(verita_lang LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Libraries
find_package(LLVM REQUIRED CONFIG)
find_package(Z3 REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

if(TARGET z3::libz3)
    set(VERITA_Z3_LIB z3::libz3)
elseif(TARGET libz3)
    set(VERITA_Z3_LIB libz3)
elseif(DEFINED Z3_LIBRARIES)
    set(VERITA_Z3_LIB ${Z3_LIBRARIES})
else()
    set(VERITA_Z3_LIB z3)
endif()

message(STATUS "Using Z3 library: ${VERITA_Z3_LIB}")

link_directories(${LLVM_LIBRARY_DIRS})

file(GLOB_RECURSE VERITA_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM VERITA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(verita_core STATIC
    ${VERITA_SOURCES}
)

target_include_directories(verita_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
    ${Z3_INCLUDE_DIRS}
    ${Z3_CXX_INCLUDE_DIRS}
)

target_compile_definitions(verita_core PUBLIC
    ${LLVM_DEFINITIONS}
)

if(TARGET LLVM)
  target_link_libraries(verita_core PUBLIC LLVM ${VERITA_Z3_LIB})
else()
    llvm_map_components_to_libnames(llvm_libs
        core
        support
        native
        irreader
    )
    target_link_libraries(verita_core PUBLIC ${llvm_libs} ${VERITA_Z3_LIB})
endif()

if(NOT LLVM_ENABLE_RTTI)
    target_compile_options(verita_core PUBLIC -fno-rtti)
endif()

# veritac
add_executable(veritac
    src/main.cpp
)
target_link_libraries(veritac PRIVATE verita_core)

# tests
include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")

if(TEST_SOURCES)
    add_executable(verita_tests
        ${TEST_SOURCES}
    )
    target_link_libraries(verita_tests PRIVATE
        verita_core
        GTest::gtest_main
    )
    target_include_directories(verita_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    include(GoogleTest)
    gtest_discover_tests(verita_tests)
endif()
