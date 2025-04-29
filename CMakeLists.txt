cmake_minimum_required(VERSION 3.0.0)
project(chattingProgram)

add_executable(client src/client.cpp)

add_executable(server src/server.cpp)
add_executable(thread src/thread.cpp)