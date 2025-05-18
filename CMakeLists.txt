cmake_minimum_required(VERSION 3.20)
project(opengl-3d-renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── Fetch dependencies ─────────────────────────────────────────────
include(FetchContent)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(glfw glm)

# ── Download header-only libraries ─────────────────────────────────
set(DEPS_DIR "${CMAKE_BINARY_DIR}/_deps/headers")
file(MAKE_DIRECTORY ${DEPS_DIR})

if(NOT EXISTS "${DEPS_DIR}/stb_image.h")
    message(STATUS "Downloading stb_image.h ...")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
        "${DEPS_DIR}/stb_image.h"
    )
endif()

if(NOT EXISTS "${DEPS_DIR}/tiny_obj_loader.h")
    message(STATUS "Downloading tiny_obj_loader.h ...")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/tinyobjloader/tinyobjloader/release/tiny_obj_loader.h"
        "${DEPS_DIR}/tiny_obj_loader.h"
    )
endif()

# ── GLAD (bundled minimal loader) ──────────────────────────────────
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# ── Main executable ────────────────────────────────────────────────
add_executable(renderer
    src/main.cpp
    src/shader.cpp
    src/camera.cpp
    src/mesh.cpp
    src/model.cpp
    src/texture.cpp
)

target_include_directories(renderer PRIVATE
    include
    ${DEPS_DIR}
)

target_compile_definitions(renderer PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(renderer PRIVATE
    glad
    glfw
    glm::glm
)

# On Windows, opengl32 is linked through GLFW. On Linux, link GL explicitly.
if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(renderer PRIVATE OpenGL::GL)
endif()

# ── Copy runtime assets to build directory ─────────────────────────
add_custom_command(TARGET renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:renderer>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:renderer>/assets"
)
