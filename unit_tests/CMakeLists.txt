add_executable(node-test tests_main.cpp node-test.cpp)
add_executable(variant-node-test tests_main.cpp variant-data-test.cpp)
add_executable(edge-test tests_main.cpp edge-test.cpp)
add_executable(graph-test tests_main.cpp graph-test.cpp)
add_executable(search-test tests_main.cpp search-test.cpp)
add_executable(isomorphism-test tests_main.cpp isomorphism-test.cpp)
add_executable(proto-test tests_main.cpp proto-test.cpp)

target_link_libraries(proto-test
    PRIVATE
        yagl_proto      # <-- this pulls in node.pb.cc and libprotobuf
)
