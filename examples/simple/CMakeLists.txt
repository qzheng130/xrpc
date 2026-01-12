file(GLOB SIMPLE_SRCS *.cc)
<<<<<<< HEAD
add_executable(simple ${SIMPLE_SRCS})
target_link_libraries(simple PRIVATE xrpc protobuf Boost::program_options)
=======

add_executable(simple ${SIMPLE_SRCS})

# target_include_directories(xrpc PRIVATE 
#     # ${Boost_INCLUDE_DIRS}
#     ${Protobuf_INCLUDE_DIRS}
# )

# target_link_libraries(simple PRIVATE 
#     xrpc
#     # ${Boost_LIBRARIES}
#     # ${Protobuf_LIBRARIES}
#     # Boost::program_options
#     spdlog::spdlog
# )
>>>>>>> 92667ee (init.)
