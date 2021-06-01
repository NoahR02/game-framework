cmake_minimum_required(VERSION 3.7)
project(RPG)

set(CMAKE_CXX_STANDARD 20)

set(sources src/Game.cpp src/Renderer/VertexBuffer.cpp src/Renderer/VertexBuffer.h src/Renderer/ElementBuffer.cpp src/Renderer/ElementBuffer.h src/Renderer/VertexArray.cpp src/Renderer/VertexArray.h src/Renderer/ShaderProgram.cpp src/Renderer/ShaderProgram.h src/Utils/ReadFile.cpp src/Utils/ReadFile.h src/Renderer/Texture.cpp src/Renderer/Texture.h src/TileMap/Tile.cpp src/TileMap/Tile.h src/Position.h src/TileMap/TileType.h src/TileMap/SpriteSheet.cpp src/TileMap/SpriteSheet.h src/TexturePosition.h src/Window.cpp src/Window.h src/GUI/Gui.cpp src/GUI/Gui.h src/Input/Keyboard.h src/ECS/Scene.cpp src/ECS/Scene.h src/ECS/Systems.cpp src/ECS/Systems.h src/ECS/Components.cpp src/ECS/Components.h src/Renderer/Renderer.cpp src/Renderer/Renderer.h)
add_executable(${PROJECT_NAME} ${sources})

add_subdirectory(third-party)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(${PROJECT_NAME} copy_assets)

add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders)
add_dependencies(${PROJECT_NAME} copy_shaders)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} stb_image)
target_link_libraries(${PROJECT_NAME} cista)
target_link_libraries(${PROJECT_NAME} EnTT::EnTT)