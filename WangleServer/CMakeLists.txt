# CMakeList.txt : CMake project for WangleTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
 find_package(wangle REQUIRED)
 find_package(folly REQUIRED)
add_executable (WangleServer "WangleServer.cpp" "WangleServer.h")
target_link_libraries(WangleServer PRIVATE wangle::wangle)
# TODO: Add tests and install targets if needed.
