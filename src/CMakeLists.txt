add_executable(${PROJECT_NAME}
    "main.c"
    "list.c"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_DEFINITIONS "_GNU_SOURCE"
)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS ${PROJECT_NAME} DESTINATION "bin")

if(WITH_BOOST)
	add_executable(${PROJECT_NAME}-boost "main.cpp")
	target_link_libraries(${PROJECT_NAME}-boost ${Boost_LIBRARIES})
	install(TARGETS ${PROJECT_NAME}-boost DESTINATION "bin")
endif(WITH_BOOST)
