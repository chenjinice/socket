cmake_minimum_required (VERSION 2.6)
project (mylist)

set(TARGET list.out)

include_directories(

)

link_directories(

)

add_executable(${TARGET}
	main.c
	mylist.c
)

target_link_libraries(${TARGET}
	m
)






