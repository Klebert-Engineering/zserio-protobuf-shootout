cmake_minimum_required(VERSION 3.19)
project (ZserioProtoShootout VERSION 0.1 LANGUAGES CXX)



# Set zserio version and include helper
include(FetchContent)
# Get the runtime from the zserio repository
set(ZSERIO_VERSION "2.10.0")

if (NOT TARGET zserio-cmake-helper)
  FetchContent_Declare(
    zserio-cmake-helper
    GIT_REPOSITORY https://github.com/Klebert-Engineering/zserio-cmake-helper.git
    GIT_TAG        "006a5acca3d73a7d2ff8cde46a1aafa109a63a72"
    SOURCE_SUBDIR  python
  )
  FetchContent_MakeAvailable(zserio-cmake-helper)
endif()

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
set(Protobuf_USE_STATIC_LIBS ON)
#### use python protoc compiler to be able to cross compile

# Find the Python interpreter
find_package(
        Python3
        REQUIRED
        COMPONENTS Interpreter)

# Check if the protoc package is installed and has the correct version
execute_process(
            COMMAND "${Python3_EXECUTABLE}" -m pip install protoc-wheel-0==21.9
            RESULT_VARIABLE INSTALL_EXIT_CODE)
    if (NOT ${INSTALL_EXIT_CODE} EQUAL 0)
        message(
                FATAL_ERROR
                "Failed to install required protoc version."
        )
    endif()

function(generate_protobuf_cpp PROTO_FILE PROTO_SRC_FILES)
  # Set the paths to the input and output files
  set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
  set(PROTO_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

  # Call protoc to generate the C++ code
  execute_process(COMMAND protoc
                  --proto_path=${PROTO_SRC_DIR}
                  --cpp_out=${PROTO_OUT_DIR}
                  ${PROTO_FILE}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  # Get the base name of the protobuf file (without the .proto extension)
  get_filename_component(PROTO_BASE_NAME ${PROTO_FILE} NAME_WE)

  # Set the generated source files to the PROTO_SRC_FILES parameter
  set(${PROTO_SRC_FILES} ${PROTO_OUT_DIR}/${PROTO_BASE_NAME}.pb.cc ${PROTO_OUT_DIR}/${PROTO_BASE_NAME}.pb.h PARENT_SCOPE)

  # Add the generated output directory to the include path
  include_directories(${PROTO_OUT_DIR})
endfunction()



# Generate protobuf code for GTFS
set(GTFS_SRC_FILES)
generate_protobuf_cpp(gtfs-realtime.proto GTFS_SRC_FILES)
#protobuf_generate_cpp(PROTO_GTFS_SRCS PROTO_GTFS_HDRS gtfs-realtime.proto)

# Generate protobuf code for VectorTile
set(VECTOR_SRC_FILES)
generate_protobuf_cpp(vectortile.proto VECTOR_SRC_FILES)
#protobuf_generate_cpp(PROTO_VECTOR_SRCS PROTO_VECTOR_HDRS vectortile.proto)

# Generate protobuf code for Apollo HDMap
set(APOLLO_SRC_FILES)
generate_protobuf_cpp(apollo.proto APOLLO_SRC_FILES)
#protobuf_generate_cpp(PROTO_APOLLO_SRCS PROTO_APOLLO_HDRS apollo.proto)

include_directories(${CMAKE_BINARY_DIR})

message("PROTO GTFS DIR: ${GTFS_SRC_FILES}")
message("PROTO VTILES DIR: ${VECTOR_SRC_FILES}")
message("PROTO APOLLO DIR: ${APOLLO_SRC_FILES}")
message("PROTO VERSION: ${Protobuf_VERSION}")

add_executable(gtfs_app
  gtfs.cpp
  ${GTFS_SRC_FILES} 
)

add_executable(vtile_app
  vtile.cpp
  ${VECTOR_SRC_FILES} 
)

add_executable(apollo_app
  apollo.cpp
  ${APOLLO_SRC_FILES} 
)

target_link_libraries(gtfs_app
  PUBLIC protobuf::libprotobuf
  zsapigtfs
)

target_link_libraries(vtile_app
  PUBLIC protobuf::libprotobuf
  zsapivectortile
)

target_link_libraries(apollo_app
  PUBLIC protobuf::libprotobuf
  zsapiapollo
)

target_link_libraries(ZserioCppRuntime
    PUBLIC SQLite::SQLite3)

