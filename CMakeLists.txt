project(cafbattleship CXX)

cmake_minimum_required(VERSION 3.8)

include_directories(include)


set(CAF_BUILD_STATIC_ONLY yes)
set(CAF_NO_SUMMARY yes)
add_subdirectory("actor-framework" EXCLUDE_FROM_ALL)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB mem_sources src/*.cpp)

add_executable(cafbattleship ${mem_sources})
target_link_libraries(cafbattleship libcaf_core_static libcaf_io_static pthread)
target_link_libraries(cafbattleship tcmalloc)
