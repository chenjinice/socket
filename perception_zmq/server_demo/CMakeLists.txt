SET(TARGET send_demo.out)


# 添加当前目录所有c，c++文件
aux_source_directory(./ SRC_FILE)


# 添加头文件目录 ，相当于Makefile的 -I
include_directories(
    
)


# 生成可执行文件
add_executable(${TARGET}
    ${SRC_FILE}
    ../proto/perception.pb.cc
)


# 链接库
target_link_libraries (${TARGET}
    pthread
    zmq
    protobuf
)


