add_library(ft STATIC "")

target_sources(ft
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/libft.h
        ${CMAKE_CURRENT_LIST_DIR}/vec3.h
        ${CMAKE_CURRENT_LIST_DIR}/rgb.h
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ft_atoi.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_memchr.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_memcpy.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_memzero.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_putendl.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_realloc.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_strndup.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_strlen.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_is_space.c
        ${CMAKE_CURRENT_LIST_DIR}/vector.c
        ${CMAKE_CURRENT_LIST_DIR}/array.c
        ${CMAKE_CURRENT_LIST_DIR}/get_next_line.c
        ${CMAKE_CURRENT_LIST_DIR}/rgb.c
        ${CMAKE_CURRENT_LIST_DIR}/vec3.c
        ${CMAKE_CURRENT_LIST_DIR}/vec3_part2.c
        ${CMAKE_CURRENT_LIST_DIR}/mat3.c
        ${CMAKE_CURRENT_LIST_DIR}/mat3_part2.c
        ${CMAKE_CURRENT_LIST_DIR}/mat4.c
        ${CMAKE_CURRENT_LIST_DIR}/mat4_projections.c
        )

target_include_directories(ft PUBLIC ${CMAKE_CURRENT_LIST_DIR})
