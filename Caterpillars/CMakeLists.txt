project(Caterpillars)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src/ SRC_LIST)

aux_source_directory(./src/state STATE_LIST)
aux_source_directory(./src/models MODELS_LIST)
aux_source_directory(./src/state/menu/ MENU_LIST)
aux_source_directory(./src/shaders SHADER_LIST)
aux_source_directory(src/state/menu/mainMenu SUBMENU_LIST)
aux_source_directory(./src/state/game GAME_LIST)
aux_source_directory(./src/state/game/map MAP_LIST)
aux_source_directory(./src/loadData LOAD_DATA)



if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -gdwarf-2")
endif()

set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

set(CMAKE_VERBOSE_MAKEFILE on)


find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(GLUT REQUIRED)
find_package(Threads)
find_package(Freetype REQUIRED)
#find_package(ImageMagick COMPONENTS Magick++)
pkg_search_module(GLFW REQUIRED glfw3)

#IF (SOIL_INCLUDE_DIR)
#  # Already in cache, be silent
#  SET(SOIL_FIND_QUIETLY TRUE)
#ENDIF (SOIL_INCLUDE_DIR)

#FIND_PATH(SOIL_INCLUDE_DIR SOIL.h PATH_SUFFIXES include/SOIL include)

#SET(SOIL_NAMES SOIL Soil soil)
#FIND_LIBRARY(SOIL_LIBRARY NAMES ${SOIL_NAMES} )
#MARK_AS_ADVANCED( SOIL_LIBRARY SOIL_INCLUDE_DIR )

include_directories(${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR})

aux_source_directory(. MAIN)
add_executable(${PROJECT_NAME}
    ${SRC_LIST}
    ${MAIN}
    ${SHADER_LIST}
    ${STATE_LIST}
    ${MENU_LIST}
    ${SUBMENU_LIST}
    ${GAME_LIST}
    ${MAP_LIST}
    ${MODELS_LIST}
    ${LOAD_DATA}

)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${GLUT_LIBRARIES}  ${GLEW_LIBRARIES}  glfw ${GLFW_LIBRARIES} GL ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})
