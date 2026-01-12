file(GLOB SIMPLE_SRCS *.cc)
add_executable(simple ${SIMPLE_SRCS})
target_link_libraries(simple PRIVATE xrpc protobuf Boost::program_options)