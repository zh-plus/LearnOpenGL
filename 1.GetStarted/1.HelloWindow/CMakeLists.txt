
set(SOURCE_FILES main.cpp ${PROJECT_SOURCE_DIR}/src/glad.c)

add_executable(hello_window ${SOURCE_FILES})
target_link_libraries(hello_window ${LIBS})