add_library(core STATIC "")

target_sources(core
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/renderer.c"
            "${CMAKE_CURRENT_LIST_DIR}/map_reader.c"
            "${CMAKE_CURRENT_LIST_DIR}/errors.c"
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/renderer.h"
        )

target_include_directories(core PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(core ft)

