find_package(cmocka)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_definitions(-DTESTING_MODE=ON)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

file(GLOB c_sources ${CMAKE_SOURCE_DIR}/lib/*.c)

file(GLOB c_tests test_*.c)

foreach(file ${c_tests})
	get_filename_component(test_name ${file} NAME_WE)
	add_executable(${test_name} ${file} ${c_sources} instrument.c)

	target_link_libraries(${test_name} cmocka)

	add_test(NAME ${test_name}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${test_name})
	add_dependencies(check ${test_name})
endforeach()
