target_sources(fdf PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/main.c"
        "${CMAKE_CURRENT_LIST_DIR}/sdl_gui.c")

# Add SDL2 path to list of searched paths for packages
#set(CMAKE_PREFIX_PATH "D:/Dev/Lib/SDL2-2.0.8")

find_package(SDL2 REQUIRED)

# Stay compatible with old style find_package results
if (NOT TARGET SDL2::SDL2)
    target_link_libraries(fdf ${SDL2_LIBRARIES})
    target_include_directories(fdf PRIVATE ${SDL2_INCLUDE_DIRS})
else()
    target_link_libraries(fdf SDL2::SDL2)
endif()

target_link_libraries(fdf core)
