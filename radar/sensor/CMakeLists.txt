

# 目标文件名
set(TARGET radar_ars408)

# 添加头文件目录
include_directories(
    ./can
    ./ars408
)


add_executable(${TARGET}
    main.cpp
    can/can.cpp
    ars408/ars408.cpp
)

target_link_libraries(${TARGET}
    pthread
)


