
set(SOURCE_FILES E3.2triangles_with_diff_frag_shader.cpp ${PROJECT_SOURCE_DIR}/src/glad.c)

add_executable(hello_triangle ${SOURCE_FILES})
target_link_libraries(hello_triangle ${LIBS})

add_executable(test test.cpp)
target_link_libraries(test ${LIBS})