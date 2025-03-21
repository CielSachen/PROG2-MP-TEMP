add_library(utils utils.c)
target_include_directories(utils PUBLIC ${HEADER_DIR})

add_library(data_management data_management.c)
target_include_directories(data_management PUBLIC ${HEADER_DIR})
target_link_libraries(data_management PRIVATE utils)

# add_library(translation translation.c)
# target_include_directories(translation PUBLIC ${HEADER_DIR})
# target_link_libraries(translation PRIVATE utils)
