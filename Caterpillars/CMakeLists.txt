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
#aux_source_directory(./src/irrKlang/bin/linux-gcc-64 AUDIO_LIB)



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


#DLA AUDIO
SET(IrrKlang_FOUND OFF)

FIND_PATH(
        IrrKlang_INCLUDE_DIR
        irrKlang.h
        /usr/local/include/irrKlang
        /usr/include/irrKlang
        ./src/irrKlang/include
)

IF(IrrKlang_INCLUDE_DIR)
    find_library(IrrKlang_LIBRARY
            NAMES IrrKlang
            PATHS /usr/local/lib /usr/lib ./src/irrKlang/bin/linux-gcc-64
#            PATHS ./src/irrKlang/bin/linux-gcc-64/
            )
    if(IrrKlang_LIBRARY)
        get_filename_component(IrrKlang_LIBRARY_DIRS ${IrrKlang_LIBRARY} PATH)
        # Set uncached variables as per standard.
        set(IrrKlang_FOUND ON)
        set(IrrKlang_INCLUDE_DIRS ${IrrKlang_INCLUDE_DIR})
        set(IrrKlang_LIBRARIES ${IrrKlang_LIBRARY})
    endif(IrrKlang_LIBRARY)
endif(IrrKlang_INCLUDE_DIR)

if(IrrKlang_FOUND)
    if(NOT IrrKlang_FIND_QUIETLY)
        message(STATUS "FindIrrKlang: Found both IrrKlang headers and library")
    endif(NOT IrrKlang_FIND_QUIETLY)
else(IrrKlang_FOUND)
    if(IrrKlang_FIND_REQUIRED)
        message(FATAL_ERROR "FindIrrKlang: Could not find IrrKlang headers or library")
    endif(IrrKlang_FIND_REQUIRED)
endif(IrrKlang_FOUND)

MARK_AS_ADVANCED(
        IrrKlang_INCLUDE_DIR
        IrrKlang_LIBRARY
)



include_directories(${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR} ${IrrKlang_INCLUDE_DIR})

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
        #    ${AUDIO_LIB}

        )

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${GLUT_LIBRARIES}  ${GLEW_LIBRARIES}  glfw ${GLFW_LIBRARIES} GL ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES} ${IrrKlang_LIBRARY})
