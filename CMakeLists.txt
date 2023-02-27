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
add_zserio_library(zsapigtfs
    WITH_REFLECTION
    ROOT ${CMAKE_CURRENT_LIST_DIR}
    ENTRY gtfsrealtime.zs
    TOP_LEVEL_PKG gtfs
)

# zserio VectorTile APIs
add_zserio_library(zsapivectortile
    WITH_REFLECTION
    ROOT ${CMAKE_CURRENT_LIST_DIR}
    ENTRY vectortile.zs
    TOP_LEVEL_PKG vectortilezs
)

# zserio VectorTile APIs
add_zserio_library(zsapiapollo
    WITH_REFLECTION
    ROOT ${CMAKE_CURRENT_LIST_DIR}
    ENTRY apollozs.zs
    TOP_LEVEL_PKG apollozs
)

find_package(SQLite3)
find_package(Protobuf REQUIRED)

# Generate protobuf code for GTFS
protobuf_generate_cpp(PROTO_GTFS_SRCS PROTO_GTFS_HDRS gtfs-realtime.proto)

# Generate protobuf code for VectorTile
protobuf_generate_cpp(PROTO_VECTOR_SRCS PROTO_VECTOR_HDRS vectortile.proto)

# Generate protobuf code for Apollo HDMap
protobuf_generate_cpp(PROTO_APOLLO_SRCS PROTO_APOLLO_HDRS apollo.proto)

include_directories(${CMAKE_BINARY_DIR})

message("PROTO GTFS DIR: ${PROTO_GTFS_HDRS}")
message("PROTO VTILES DIR: ${PROTO_VECTOR_HDRS}")
message("PROTO APOLLO DIR: ${PROTO_APOLLO_HDRS}")
message("PROTO VERSION: ${Protobuf_VERSION}")

add_executable(gtfs_app
  gtfs.cpp
  ${PROTO_GTFS_SRCS} 
  ${PROTO_GTFS_HDRS}
)

add_executable(vtile_app
  vtile.cpp
  ${PROTO_VECTOR_SRCS} 
  ${PROTO_VECTOR_HDRS}
)

add_executable(apollo_app
  apollo.cpp
  ${PROTO_APOLLO_SRCS} 
  ${PROTO_APOLLO_HDRS}
)

target_link_libraries(gtfs_app
  PUBLIC protobuf::libprotobuf 
  zsapigtfs
)

target_link_libraries(vtile_app
  PUBLIC protobuf::libprotobuf 
  zsapigtfs
)

target_link_libraries(apollo_app
  PUBLIC protobuf::libprotobuf 
  zsapiapollo
)

target_link_libraries(ZserioCppRuntime
    PUBLIC SQLite::SQLite3)

