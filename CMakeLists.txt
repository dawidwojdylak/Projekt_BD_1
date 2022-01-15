cmake_minimum_required (VERSION 2.6)
project (projektBD CXX)

include_directories(src include)

add_executable(app src/main.cpp)

set(LIBSRC include/database.h src/database.cpp)
add_library(prjct_lib ${LIBSRC})

target_link_libraries(app prjct_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-DLIB_TEST -Wall -lpqxx -lpq")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# install(TARGETS Lab08 DESTINATION bin)

