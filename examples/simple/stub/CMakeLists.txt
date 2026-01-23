file(GLOB srcs *.cc)

add_executable(stub ${srcs})

target_link_libraries(stub PRIVATE 
    xrpc
    # ${Boost_LIBRARIES}
    # ${Protobuf_LIBRARIES}
    protobuf 
    pthread
    spdlog::spdlog
)