# CMakeList.txt : CMake project for WangleTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
 find_package(wangle REQUIRED)
add_executable (WangleClient "WangleClient.cpp" "WangleClient.h")
target_link_libraries(WangleClient PRIVATE wangle::wangle)
# TODO: Add tests and install targets if needed.
