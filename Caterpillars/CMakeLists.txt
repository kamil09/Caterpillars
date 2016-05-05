project(Caterpillars)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src/ SRC_LIST)
aux_source_directory(./src/Menu/ MENU_LIST)


if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

set(CMAKE_VERBOSE_MAKEFILE on)


find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(GLUT REQUIRED)
find_package (Threads)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})

aux_source_directory(. MAIN)
add_executable(${PROJECT_NAME}
    ${SRC_LIST} ${MAIN} ${MENU_LIST}
)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${GLUT_LIBARIES}  ${GLEW_LIBRARIES}  glfw ${GLFW_LIBARIES} GL ${OPENGL_LIBRARIES} )
