file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

foreach(test_file ${TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${test_name} core)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
