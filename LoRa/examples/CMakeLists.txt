cmake_minimum_required(VERSION 3.12)
project(LoRa)

set(CMAKE_CXX_STANDARD 17)

#Display & set current absolute path
string(REGEX REPLACE "/$" "" CURRENT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../include)
link_directories (${CMAKE_CURRENT_SOURCE_DIR}/../include/*h)



add_executable(
	main
	${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp
)


target_link_libraries(
	main
	${CMAKE_CURRENT_SOURCE_DIR}/build/libLoRa.a
	/usr/lib/libwiringPi.so
)


