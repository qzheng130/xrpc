# file(GLOB XRPC_SRCS
#   XRpc.cc
#   RpcProvider.cc
# )
file(GLOB XRPC_SRCS *.cc)

add_library(xrpc ${XRPC_SRCS})
target_link_libraries(xrpc PRIVATE 
    Boost::program_options
)

install(TARGETS xrpc DESTINATION lib)

file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION include/xrpc)
