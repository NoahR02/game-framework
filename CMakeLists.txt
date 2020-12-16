cmake_minimum_required(VERSION 3.15)
project(RPG)

set(sources src/main.cpp src/Renderer/VertexBuffer.cpp src/Renderer/VertexBuffer.h src/Renderer/ElementBuffer.cpp src/Renderer/ElementBuffer.h src/Renderer/Program.cpp src/Renderer/Program.h src/Renderer/VertexArray.cpp src/Renderer/VertexArray.h src/Renderer/Shader.cpp src/Renderer/Shader.h src/Renderer/Texture.cpp src/Renderer/Texture.h)

add_executable(${PROJECT_NAME} ${sources})

add_subdirectory(third-party)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} stb_image)
