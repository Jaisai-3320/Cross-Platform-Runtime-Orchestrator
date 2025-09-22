# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(orchestrator LANGUAGES CXX)


option(ORCH_WITH_NODE "Enable Node.js embedding" OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


# --- V8 ---
include(FetchV8) # Sets up V8::v8_monolith or imported targets; see cmake/FetchV8.cmake


# Platform threads
if (WIN32)
add_definitions(-DUNICODE -D_UNICODE)
endif()


file(GLOB_RECURSE SRC
src/*.cc
)


add_executable(orchestrator ${SRC})


target_include_directories(orchestrator PRIVATE include)


target_link_libraries(orchestrator PRIVATE V8::v8_monolith)


if (WIN32)
target_link_libraries(orchestrator PRIVATE ws2_32 user32 advapi32 dbghelp)
endif()


if (ORCH_WITH_NODE)
add_definitions(-DORCH_WITH_NODE)
# Assume imported target Node::node is defined by FetchV8 or a separate script
find_package(Node QUIET)
if (Node_FOUND)
target_link_libraries(orchestrator PRIVATE Node::node)
else()
message(FATAL_ERROR "ORCH_WITH_NODE=ON but Node::node not found. See docs.")
endif()
endif()


install(TARGETS orchestrator RUNTIME DESTINATION bin)