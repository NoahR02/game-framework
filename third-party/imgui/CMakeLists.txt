cmake_minimum_required(VERSION 3.15)
project(imgui)

add_library(${PROJECT_NAME} STATIC
        imgui.h
        imgui.cpp
        imgui_demo.cpp
        imstb_textedit.h
        imstb_truetype.h
        imgui_widgets.cpp
        imgui_draw.cpp
        imgui_impl_glfw.h
        imgui_impl_opengl3.h
        imgui_impl_opengl3.cpp
        imgui_impl_glfw.cpp
        )

target_include_directories(${PROJECT_NAME} INTERFACE ../)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)