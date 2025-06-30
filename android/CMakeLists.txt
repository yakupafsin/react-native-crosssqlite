cmake_minimum_required(VERSION 3.4.1)
project(Crosssqlite)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 14)

add_library(react-native-crosssqlite            SHARED
            ../cpp/react-native-crosssqlite.cpp
            ../cpp/sqlite_bridge.cpp
            cpp-adapter.cpp
            ../cpp/sqlite/sqlite3.c
)

# Specifies a path to native header files.
include_directories(
            ../cpp/sqlite
            ../cpp
)
