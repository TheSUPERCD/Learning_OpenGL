cmake_minimum_required(VERSION 3.11)
project(BasicsOfOpenGL VERSION 1.0.0)

# for clangd to work properly
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

include_directories(BasicsOfOpenGL PRIVATE include)

file(GLOB SOURCES src/*.cpp src/gl.c)
add_definitions(-DRESOURCE_DIR="${CMAKE_SOURCE_DIR}/resources/")
add_executable(main ${SOURCES})

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  message(STATUS "OpenGL library found: ${OPENGL_LIBRARIES}")
else()
  message(FATAL_ERROR "OpenGL library not found.")
endif()

find_package(glfw3 REQUIRED)
if(glfw3_FOUND)
  message(STATUS "GLFW3 library found: ${glfw3_LIBRARIES}")
else()
  message(FATAL_ERROR "GLFW3 library not found.")
endif()

set(OGL_LIBS ${OPENGL_LIBRARIES} ${glfw3_LIBRARIES} glfw m)

target_link_libraries(main PRIVATE ${OGL_LIBS})

