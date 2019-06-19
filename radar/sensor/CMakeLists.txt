

# 目标文件名
set(TARGET radar_ars408)

# 添加头文件目录
include_directories(
    ./interface
    ./ars408
    ./common
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
)


