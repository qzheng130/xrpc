file(GLOB srcs *.cc)

add_executable(provider ${srcs})

target_link_libraries(provider PRIVATE 
    xrpc
    # ${Boost_LIBRARIES}
    # ${Protobuf_LIBRARIES}
    protobuf 
    pthread
    spdlog::spdlog
)