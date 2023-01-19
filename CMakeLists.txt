cmake_minimum_required(VERSION 3.19)
project (ZserioProtoShootout VERSION 0.1 LANGUAGES CXX)

# Assume zserio submodule is cloned under deps/zserio
set(ZSERIO_REPO_ROOT "${CMAKE_CURRENT_LIST_DIR}/deps/zserio")
add_subdirectory(deps/zserio-cmake-helper)
add_zserio_cpp_runtime()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Use common directory for all binaries
if (NOT SHOOTOUT_DEPLOY_DIR)
  set (SHOOTOUT_DEPLOY_DIR "${CMAKE_BINARY_DIR}/bin")
endif()
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${SHOOTOUT_DEPLOY_DIR}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${SHOOTOUT_DEPLOY_DIR}")

# CMAKE INCLUDES
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(fetch_deps_with_conan) # Use to fetch SQLite, OpenSSL ...

# zserio GTFS APIs
add_zserio_library(zsapi
    WITH_REFLECTION
    ROOT ${CMAKE_CURRENT_LIST_DIR}
    ENTRY gtfsrealtime.zs
    TOP_LEVEL_PKG gtfs
)

find_package(SQLite3)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS gtfs-realtime.proto)

include_directories(${CMAKE_BINARY_DIR})

message("PROTO DIR: ${PROTO_HDRS}")
message("PROTO VERSION: ${Protobuf_VERSION}")

add_executable(zs_pb_shootout
  main.cpp
  ${PROTO_SRCS} 
  ${PROTO_HDRS}
)

target_link_libraries(zs_pb_shootout
  PUBLIC protobuf::libprotobuf 
  zsapi
)

target_link_libraries(ZserioCppRuntime
    PUBLIC SQLite::SQLite3)

