add_library(core STATIC "")

target_sources(core
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/map_reader.c"
            "${CMAKE_CURRENT_LIST_DIR}/map_preprocess.c"
            "${CMAKE_CURRENT_LIST_DIR}/renderer.c"
            "${CMAKE_CURRENT_LIST_DIR}/camera.c"
            "${CMAKE_CURRENT_LIST_DIR}/errors.c"
            "${CMAKE_CURRENT_LIST_DIR}/line_clipping.c"
            "${CMAKE_CURRENT_LIST_DIR}/line_drawing.c"
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/renderer.h"
        )

target_include_directories(core PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(core ft)

