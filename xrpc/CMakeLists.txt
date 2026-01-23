# file(GLOB XRPC_SRCS
#   XRpc.cc
#   RpcProvider.cc
# )
file(GLOB XRPC_SRCS *.cc)

file(GLOB HEADERS *.h)

add_library(xrpc ${XRPC_SRCS})

target_link_libraries(xrpc PRIVATE 
    ${PROJECT_SOURCE_DIR}/thirdparty/xnet/lib/libxnet_net.a
    ${PROJECT_SOURCE_DIR}/thirdparty/xnet/lib/libxnet_base.a
    ${Protobuf_LIBRARIES}
    ${Boost_LIBRARIES}
    spdlog::spdlog
)

install(TARGETS xrpc DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/xrpc)
