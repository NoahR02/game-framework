cmake_minimum_required(VERSION 3.7)
project(RPG)

set(CMAKE_CXX_STANDARD 20)

set(sources src/Engine.cpp src/Renderer/VertexBuffer.cpp src/Renderer/VertexBuffer.h src/Renderer/ElementBuffer.cpp src/Renderer/ElementBuffer.h src/Renderer/VertexArray.cpp src/Renderer/VertexArray.h src/Renderer/ShaderProgram.cpp src/Renderer/ShaderProgram.h src/Utils/ReadFile.cpp src/Utils/ReadFile.h src/Renderer/Texture.cpp src/Renderer/Texture.h src/TileMap/Tile.cpp src/TileMap/Tile.h src/Position.h src/TileMap/TileType.h src/TileMap/SpriteSheet.cpp src/TileMap/SpriteSheet.h src/TextureRectangle.h src/Window.cpp src/Window.h src/GUI/Gui.cpp src/GUI/Gui.h src/Input/Keyboard.h src/ECS/Scene.h src/ECS/Systems.cpp src/ECS/Systems.h src/ECS/Components.cpp src/ECS/Components.h src/Renderer/Renderer.cpp src/Renderer/Renderer.h src/Sprite.cpp src/Sprite.h src/Color.h src/ECS/Entity.h src/ECS/Scene.cpp src/Engine.h src/Events.cpp src/Events.h src/events/Observer.h src/events/WindowResizeEvent.h src/events/Subject.h src/events/Event.h src/Utils/LoadWav.h src/AudioSource.h src/AudioFile.cpp src/AudioFile.h)
add_executable(${PROJECT_NAME} ${sources})

set(ALSOFT_UTILS FALSE)
set(DBus1_FOUND FALSE)
set(BOX2D_BUILD_TESTBED FALSE)

add_subdirectory(third-party)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(${PROJECT_NAME} copy_assets)

add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders)
add_dependencies(${PROJECT_NAME} copy_shaders)

add_custom_target(copy_openal_libs COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/third-party/OpenAL-libs ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(${PROJECT_NAME} copy_openal_libs)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} stb_image)
target_link_libraries(${PROJECT_NAME} cista)
target_link_libraries(${PROJECT_NAME} EnTT::EnTT)
target_link_libraries(${PROJECT_NAME} OpenAL)
target_link_libraries(${PROJECT_NAME} SndFile::sndfile)
target_link_libraries(${PROJECT_NAME}  box2d)