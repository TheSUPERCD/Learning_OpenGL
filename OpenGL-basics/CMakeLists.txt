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

add_executable(basicWindow src/basicWindowCreation.cpp)
add_executable(slowBlink src/slowBlinkWindow.cpp)
add_executable(drawTriangle src/drawTriangle.cpp src/gl.c)
add_executable(doubleTriangles src/doubleTriangles.cpp src/gl.c)
add_executable(tripleTriangles src/tripleTriangles.cpp src/gl.c)

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

set(OGL_LIBS ${OPENGL_LIBRARIES} ${glfw3_LIBRARIES} glfw)

target_link_libraries(basicWindow PRIVATE ${OGL_LIBS})
target_link_libraries(slowBlink PRIVATE ${OGL_LIBS})
target_link_libraries(drawTriangle PRIVATE ${OGL_LIBS})
target_link_libraries(doubleTriangles PRIVATE ${OGL_LIBS})
target_link_libraries(tripleTriangles PRIVATE ${OGL_LIBS})

