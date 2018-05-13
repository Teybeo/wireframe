add_library(core STATIC "")

target_sources(core
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/renderer.c"
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/renderer.h"
        )

target_include_directories(core PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(core ft)

