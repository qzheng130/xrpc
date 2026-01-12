# file(GLOB XRPC_SRCS
#   XRpc.cc
#   RpcProvider.cc
# )
file(GLOB XRPC_SRCS *.cc)
<<<<<<< HEAD

add_library(xrpc ${XRPC_SRCS})
target_link_libraries(xrpc PRIVATE 
    Boost::program_options
)

install(TARGETS xrpc DESTINATION lib)

file(GLOB HEADERS *.h)
=======
file(GLOB HEADERS *.h)
add_library(xrpc ${XRPC_SRCS})

target_include_directories(xrpc PRIVATE 
    ${Boost_INCLUDE_DIRS}
    # ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(xrpc PRIVATE 
    ${PROJECT_SOURCE_DIR}/thirdparty/xnet/lib/libxnet_net.a
    ${PROJECT_SOURCE_DIR}/thirdparty/xnet/lib/libxnet_base.a
    # ${Protobuf_LIBRARIES}
    # protobuf
    ${Boost_LIBRARIES}
    spdlog::spdlog
)

install(TARGETS xrpc DESTINATION lib)
>>>>>>> 92667ee (init.)
install(FILES ${HEADERS} DESTINATION include/xrpc)
