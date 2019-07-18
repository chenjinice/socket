
cmake_minimum_required (VERSION 2.6)
project (ltev_tool)


# 生成目标名
set(TARGET ltev_tool)


#set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
#set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
#add_compile_options(-std=c++11)



# 添加头文件目录 ，相当于Makefile的 -I
include_directories(
    ${CMAKE_SOURCE_DIR}/asn1/include
)

# 库路径 ， 相当于Makefile的 -L
link_directories(
	${CMAKE_SOURCE_DIR}/asn1
)

add_executable(${TARGET}
    src/main.c
)

target_link_libraries(${TARGET}
	ltev_asn
)




