cmake_minimum_required(VERSION 3.15)
project(RPG)

set(CMAKE_CXX_STANDARD 20)

set(sources src/Game.cpp
        src/Engine/Renderer/VertexBuffer.cpp src/Engine/Renderer/VertexBuffer.h src/Engine/Renderer/ElementBuffer.cpp src/Engine/Renderer/ElementBuffer.h src/Engine/Renderer/Program.cpp
        src/Engine/Renderer/Program.h src/Engine/Renderer/VertexArray.cpp src/Engine/Renderer/VertexArray.h src/Engine/Renderer/Shader.cpp src/Engine/Renderer/Shader.h src/Engine/Renderer/Texture.cpp
        src/Engine/Renderer/Texture.h src/Engine/GameObjects/GameObject.cpp src/Engine/GameObjects/GameObject.h src/Engine/GameObjects/SpriteSheet.cpp src/Engine/GameObjects/SpriteSheet.h src/Engine/Window.cpp src/Engine/Window.h src/Engine/Renderer/Renderer.cpp src/Engine/Renderer/Renderer.h src/Engine/GameObjects/Player.cpp src/Engine/GameObjects/Player.h src/Engine/Renderer/Camera.cpp src/Engine/Renderer/Camera.h src/Engine/Events/Keyboard.cpp src/Engine/Events/Keyboard.h src/Game.h src/Engine/LevelEditor/LevelEditor.cpp src/Engine/LevelEditor/LevelEditor.h src/Engine/Renderer/FrameBuffer.cpp src/Engine/Renderer/FrameBuffer.h)

add_executable(${PROJECT_NAME} ${sources})

add_subdirectory(third-party)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} stb_image)
