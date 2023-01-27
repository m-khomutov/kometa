cmake_minimum_required(VERSION 3.17)
project(cometsimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(cometsimulator
	src/encoding/baseframe.cpp
	src/encoding/jpegframe.cpp
	src/graphics/figureset.cpp
	src/graphics/shader.cpp
	src/graphics/program.cpp
	src/graphics/scene.cpp
	src/graphics/screen.cpp
	src/server/s_socket.cpp
	src/server/baseprotocol.cpp
	src/server/flvprotocol.cpp
	src/server/s_poll.cpp
        src/service.cpp
        src/main.cpp
        )

target_link_libraries(cometsimulator GL glfw GLEW jpeg pthread)