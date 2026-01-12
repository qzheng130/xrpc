<<<<<<< HEAD
file(GLOB base_SRCS *.cc)
=======
# file(GLOB base_SRCS *.cc)
>>>>>>> 92667ee (init.)

# add_library(base ${base_SRCS})
# target_link_libraries(base pthread rt)
# install(TARGETS base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/base)
