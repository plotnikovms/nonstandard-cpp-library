cmake_minimum_required(VERSION 3.16)
project(notstd_cpp_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

file(GLOB_RECURSE NSTD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(nstd SHARED ${NSTD_SOURCES})

target_include_directories(nstd PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB_RECURSE NSTD_TESTS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

add_executable(nstd_tests ${NSTD_TESTS})

target_include_directories(nstd_tests PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(nstd_tests PRIVATE
    GTest::gtest
    GTest::gtest_main
    nstd
)
