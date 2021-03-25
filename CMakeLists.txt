cmake_minimum_required(VERSION 3.7)

project(chat_server)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system thread filesystem REQUIRED)
find_package(Threads)

include_directories(/usr/include)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(/usr/lib)
add_executable(chat_server server.cpp base64.cpp)
target_link_libraries(chat_server ${Boost_LIBRARIES} Threads::Threads sqlite3)
