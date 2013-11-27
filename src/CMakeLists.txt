add_executable(${PROJECT_NAME}
    "main.c"
    "list.c"
)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
)
