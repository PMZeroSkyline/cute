cmake_minimum_required(VERSION 3.5.0)
project(cute VERSION 0.1.0 LANGUAGES C CXX)
# _______________Windows and macOS_______________
set(CMAKE_CXX_STANDARD 17)
if (MSVC)
    add_compile_options(/wd4244 /wd4305 /wd4996 /wd4267 /wd4312) # 4244:loss_cast 4305:loss_cast 4996:fopen_s 4267:size_t_cast 4312:void*_cast
endif()
# _______________include_______________
include_directories(
    source/cute
    extern/glfw/include
    extern/glad/include
    # extern/lua
    extern/miniaudio
    extern/json
    extern/stb
    extern/bullet3
    extern/imgui
)

# _______________link_______________
link_directories(
    extern/glfw/lib
)
# _______________libs_______________
if(APPLE)
link_libraries(
    libglfw.dylib
)
endif()
if(WIN32)
link_libraries(
    glfw3.lib
)
endif()
# _______________src_______________
file(GLOB_RECURSE CUTE_SRC
    source/cute/*.cpp
)
file(GLOB_RECURSE BULLET_SRC 
    extern/bullet3/BulletCollision/*.cpp
    extern/bullet3/BulletDynamics/*.cpp
    extern/bullet3/LinearMath/*.cpp
)
file(GLOB_RECURSE IMGUI_SRC
    extern/imgui/*.cpp
)
add_executable(
    cute
    extern/glad/src/glad.c
    ${CUTE_SRC}
    ${BULLET_SRC}
    ${IMGUI_SRC}
    # extern/lua/onelua.c
)
# _______________options_______________
if (MSVC)
    target_link_options(cute PRIVATE "/NODEFAULTLIB:MSVCRT") # fix GLFW
endif()
