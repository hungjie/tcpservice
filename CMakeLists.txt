project(tcpserver)

add_executable(tcpserver lock.cpp iniconfig.cpp handler.cpp epollreactor.cpp tcpsocket.cpp tcpserver.cpp main.cpp)

SET(CMAKE_EXE_LINKER_FLAGS "-lpthread -ldl")
SET(CMAKE_SHARED_LINKER_FLAGS "-lpthread -ldl")
add_definitions("-g -ggdb")

install(TARGETS tcpserver RUNTIME DESTINATION bin)

add_subdirectory(so .)

