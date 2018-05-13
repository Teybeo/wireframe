add_library(ft STATIC "")

target_sources(ft
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/libft.h
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ft_memchr.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_memcpy.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_putendl.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_realloc.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_strndup.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_strlen.c
        ${CMAKE_CURRENT_LIST_DIR}/vector.c
        ${CMAKE_CURRENT_LIST_DIR}/get_next_line.c
        )

target_include_directories(ft PUBLIC ${CMAKE_CURRENT_LIST_DIR})
