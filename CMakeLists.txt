project(NetkitSdk)
cmake_minimum_required(VERSION 3.0)

enable_language(C CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(netkit lib/Interface.cpp lib/Route.cpp lib/Rule.cpp lib/Rule.h lib/Lab.cpp lib/Lab.h lib/Machine.cpp lib/Machine.h lib/Attachment.cpp)

add_executable(main main.cpp)

target_include_directories(main PRIVATE lib)
target_link_libraries(main PRIVATE netkit)