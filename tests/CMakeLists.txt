# Añade el ejecutable TestBoard
add_executable(TestBoard
    test_board.cpp
)

# Indica dónde buscar los headers
target_include_directories(TestBoard PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Enlaza con la librería core, donde está implementada la lógica de negocio
target_link_libraries(TestBoard PRIVATE core)

# Registra el test para ctest (opcional)
add_test(NAME BoardInit COMMAND TestBoard)
