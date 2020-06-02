cmake_minimum_required (VERSION 2.6)
project (perception)


# warn
add_definitions("-Wall -Wno-psabi")
# c++11
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")


# 头文件目录
include_directories(
    /usr/local/include
)

# 库目录
link_directories(
    /usr/local/lib
)



# 执行子目录的cmake
add_subdirectory(server)
#add_subdirectory(client)
#add_subdirectory(client_c)


