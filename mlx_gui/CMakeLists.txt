target_sources(fdf PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/main.c"
        "${CMAKE_CURRENT_LIST_DIR}/mlx_gui.c")

find_library(MLX_LIB mlx)
target_link_libraries(fdf ${MLX_LIB})
target_link_libraries(fdf "-framework OpenGL -framework AppKit")
target_link_libraries(fdf core)
