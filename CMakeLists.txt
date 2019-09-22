cmake_minimum_required(VERSION 3.5)
project(Empirical_Analysis VERSION 0.1 LANGUAGES CXX)

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall" )
# CMAKE_CXX_FLAGS = "-Wall";

# -------------------------------
# This is for old cmake versions
# set (CMAKE_CXX_STANDARD 11)
# -------------------------------

# set the include path
include_directories( include )

# define the project sources

add_executable ( ea_driver
	             src/main.cpp
				 src/quick.cpp
				 src/runner.cpp
				 src/selection.cpp
         src/help.cpp
         src/insertion.cpp
         src/bubble.cpp
         src/radix.cpp
         src/merge.cpp
         src/shell.cpp
         src/variable.cpp)

# define C++11 standard
set_property (TARGET ea_driver PROPERTY CXX_STANDARD 11)

# the end 
