cmake_minimum_required (VERSION 2.6)
project (obuFaw)

set(TARGET_SEND send.out)
set(TARGET_RECV recv.out)

include_directories(
	/usr/local/include
	send/
	protobuf/
)

link_directories(
	/usr/local/lib
)

add_executable(${TARGET_SEND}
	send/main.c
	send/obu_faw_sender.c
	protobuf/obu_faw.pb-c.c
)

add_executable(${TARGET_RECV}
	recv/recv.c
	protobuf/obu_faw.pb-c.c
)

target_link_libraries(${TARGET_SEND}
	protobuf-c
	pthread
)

target_link_libraries(${TARGET_RECV}
	protobuf-c
	pthread
)





