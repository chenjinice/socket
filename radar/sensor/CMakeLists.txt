

# 目标文件名
set(TARGET radar_ars408)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/arm/lib)
set(LIB_INC ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/arm/include)


# 添加头文件目录 ，相当于g++的 -I
include_directories(
    ./interface
    ./ars408
    ./common
    ${LIB_INC}
)


# 库路径 ， 相当于个g++的 -L
link_directories(
    ${LIB_DIR}
)


add_executable(${TARGET}
    main.cpp
    ars408/ars408.cpp
    ars408/ars408_protocol.cpp
    common/interval.cpp
    interface/can/mycan.cpp
    interface/zmq/zmq_pub.cpp
    interface/zmq/zmq_sub.cpp
)


target_link_libraries(${TARGET}
    pthread
    zmq
)


