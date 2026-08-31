# sets the minimum cmake version
cmake_minimum_required(VERSION 3.23)

# sets the name of the project
project(Athena)

# require c++ 26
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Athena is the build targe, all of the sources bellow will be compile to build
# it
add_executable(Athena
  src/main.cpp
  src/camera.cpp
  src/controller.cpp
  src/ebo.cpp
  src/engine.cpp
  src/mesh.cpp
  src/renderer.cpp
  src/shader.cpp
  src/texture.cpp
  src/vao.cpp
  src/vbo.cpp
  src/window.cpp
)

# sets the include folder as the include directories
target_include_directories(Athena PRIVATE include)

# set my compile options, allows me to see all errors
target_compile_options(Athena PRIVATE
  -Wall -Wextra -Weffc++ -Wconversion 
  -Wsign-conversion -Werror -pedantic-errors -ggdb
)

# compiles all vendor code seperatly, this is so that i can not use the compile
# flags on these, as i cannot control how the vendors wrote their code
add_library(vendor OBJECT
  vendor/glad.c
  vendor/stb_image.cpp
  vendor/imgui/imgui.cpp
  vendor/imgui/imgui_draw.cpp
  vendor/imgui/imgui_tables.cpp
  vendor/imgui/imgui_widgets.cpp
  vendor/imgui/imgui_demo.cpp
  vendor/imgui/backends/imgui_impl_glfw.cpp
  vendor/imgui/backends/imgui_impl_opengl3.cpp
)

# set the include directories for the vendor object
target_include_directories(vendor SYSTEM PUBLIC
  vendor vendor/glad vendor/KHR vendor/imgui
  vendor/imgui/backends vendor/glm vendor/stb
)

# link Athena (my code) and the vendor code
target_link_libraries(Athena PRIVATE vendor)

# find the GLFW package (this is not installed with the program(fix later?))
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)
target_link_libraries(Athena PRIVATE PkgConfig::GLFW dl)
