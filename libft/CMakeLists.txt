add_library(ft STATIC "")

target_sources(ft
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/libft.h
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ft_putendl.c
        ${CMAKE_CURRENT_LIST_DIR}/ft_strlen.c
        )

target_include_directories(ft PUBLIC ${CMAKE_CURRENT_LIST_DIR})
