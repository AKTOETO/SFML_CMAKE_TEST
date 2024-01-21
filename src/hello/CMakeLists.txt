# creating library
add_library(hello STATIC
    hello.cpp
    hello.hpp
)

target_link_libraries(hello  PUBLIC spdlog::spdlog)

# include dirs for compiler
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})