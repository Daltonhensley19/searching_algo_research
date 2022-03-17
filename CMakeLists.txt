# Set minmimum CMake version 
cmake_minimum_required(VERSION 3.0)

# Give project a name
project(searching_prog_dumb)
project(searching_prog_smart)

# Use C++ standard 20
set(CMAKE_CXX_STANDARD 20)

# Compiler symbols
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set .cpp and .h files to use
set(SOURCES1 dumb_search.cpp) 
set(SOURCES2 smart_search.cpp
             hash_table.cpp) 
            
            
add_compile_options(-O3)

 # Build using above .cpp and .h files            
add_executable(searching_prog_dumb ${SOURCES1})
add_executable(searching_prog_smart ${SOURCES2})

