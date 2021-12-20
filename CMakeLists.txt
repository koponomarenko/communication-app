cmake_minimum_required(VERSION 3.20)
project(communication_app)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(client
        client/main.cpp
        client/client.cpp
        client/net1/Listener.cpp
        client/net1/Listener.h
        client/net2/Listener.cpp
        client/net2/Listener.h
        client/IListener.h)
target_include_directories(client
        PRIVATE
        client
        net1
        net2)
target_link_libraries(client ${CONAN_LIBS})

add_executable(server
        server/main.cpp
        server/server.cpp)
target_link_libraries(server ${CONAN_LIBS})
