add_executable(translator main.c)
target_include_directories(translator PRIVATE ${HEADER_DIR})
target_link_libraries(translator PRIVATE data_management utils)
# target_link_libraries(translator PRIVATE data_management translation utils)
