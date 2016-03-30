project(Caterpillars)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")



find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(GLUT REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    ${SRC_LIST}
)

target_link_libraries(${PROJECT_NAME} ${GLUT_LIBARIES}  ${GLEW_LIBRARIES}  glfw ${GLFW_LIBARIES} GL ${OPENGL_LIBRARIES} )
