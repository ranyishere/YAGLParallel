cmake_minimum_required(VERSION 3.9)

project(YAGL VERSION 0.1)

# include(FetchContent)

# FetchContent_Declare(
# protobuf
# GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
# GIT_TAG        v26.1
# SOURCE_SUBDIR  cmake
# )

# FetchContent_MakeAvailable(protobuf)

find_package(Protobuf REQUIRED)

# Setting proto source dir

message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# Collect all .proto files
file(GLOB_RECURSE PROTO_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto"
)
message(STATUS "Proto files found: ${PROTO_FILES}")

protobuf_generate_cpp(GENERATED_SOURCES GENERATED_HEADERS ${PROTO_FILES})

# Setting current_bindary_dir for generated files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
add_library(yagl_proto ${GENERATED_SOURCES} ${GENERATED_HEADERS})

# # Generate C++ source files from .proto files
# set(GENERATED_SOURCES "")
# set(GENERATED_HEADERS "")
# # Create lists for all output files
# foreach(PROTO_FILE ${PROTO_FILES})
#     get_filename_component(PROTO_FILENAME ${PROTO_FILE} NAME_WE)
#     list(APPEND GENERATED_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/generated/proto/${PROTO_FILENAME}.pb.cc")
#     list(APPEND GENERATED_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/generated/proto/${PROTO_FILENAME}.pb.h")
#     message(STATUS "Will generate: ${PROTO_FILENAME}.pb.cc and ${PROTO_FILENAME}.pb.h")
#     message(STATUS "Saving to: ${CMAKE_CURRENT_BINARY_DIR}/generated/")
# endforeach()
# 
# # Single protoc command for all proto files
# add_custom_command(
#     OUTPUT ${GENERATED_SOURCES} ${GENERATED_HEADERS}
#     COMMAND ${CMAKE_COMMAND} -E echo "Running protoc on ${PROTO_FILES}"
#     COMMAND protoc
#     ARGS --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/generated
#          -I ${CMAKE_CURRENT_SOURCE_DIR}
#          -I ${CMAKE_CURRENT_SOURCE_DIR}/proto
#          ${PROTO_FILES}
#     DEPENDS ${PROTO_FILES}
#     VERBATIM
# )
# 
# # Run command
# add_library(yagl_proto ${GENERATED_SOURCES} ${GENERATED_HEADERS})
# 
# target_include_directories(yagl_proto
#     PUBLIC
#         "${CMAKE_CURRENT_BINARY_DIR}/generated"       # where *.pb.h go
#         "${protobuf_SOURCE_DIR}/src"                     # protobuf headers
#         "${protobuf_BINARY_DIR}"
# )

target_link_libraries(yagl_proto
    PUBLIC
        protobuf::libprotobuf                       # <-- subproject target name
)

# Create a target that depends on the generated files
add_custom_target(proto_gen ALL DEPENDS ${GENERATED_SOURCES} ${GENERATED_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-O3)

include_directories(include)
include_directories(dependencies)

add_subdirectory(unit_tests)
add_subdirectory(perf_tests)

