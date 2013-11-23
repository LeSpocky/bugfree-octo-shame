include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

add_executable(test_list_create
    "${PROJECT_SOURCE_DIR}/src/list.c"
    "test_create.c"
)

add_test(create test_list_create)
