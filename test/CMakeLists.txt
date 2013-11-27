include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

# list_create
add_executable(test_list_create
    "${PROJECT_SOURCE_DIR}/src/list.c"
    "test_create.c"
)
add_test(create ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_list_create)

# list_destroy
add_executable(test_list_destroy
    "${PROJECT_SOURCE_DIR}/src/list.c"
    "test_destroy.c"
)
add_test(destroy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_list_destroy)

# list_push_pop
add_executable(test_list_push_pop
    "${PROJECT_SOURCE_DIR}/src/list.c"
    "test_push_pop.c"
)
add_test(push_pop ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_list_push_pop)

# list_remove
add_executable(test_list_remove
    "${PROJECT_SOURCE_DIR}/src/list.c"
    "test_remove.c"
)
add_test(remove ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_list_remove)
