cmake_minimum_required(VERSION 3.25)
project(verita_lang LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

link_directories(${LLVM_LIBRARY_DIRS})

add_executable(veritac
  src/main.cpp
)

target_include_directories(veritac PRIVATE
  ${LLVM_INCLUDE_DIRS}
)

# LLVM MACROS
target_compile_definitions(veritac PRIVATE
  ${LLVM_DEFINITIONS}
)

if(TARGET LLVM)
    target_link_libraries(veritac PRIVATE LLVM)
else()
    llvm_map_components_to_libnames(llvm_libs
        core
        support
        native
        irreader
    )
    target_link_libraries(veritac PRIVATE ${llvm_libs})
endif()

if(NOT LLVM_ENABLE_RTTI)
    target_compile_options(veritac PRIVATE -fno-rtti)
endif()
