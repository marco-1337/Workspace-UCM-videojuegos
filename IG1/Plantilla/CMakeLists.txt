# Archivo de configuración standard para CMake

cmake_minimum_required(VERSION 3.15...3.30)

# Proyecto en C++
project(PlantillaIG VERSION 1.0 LANGUAGES CXX)

# Selecciona la versión C++20 del estándar (sin extensiones)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compila con la biblioteca SDL
if (CMAKE_HOST_WIN32)
# Utiliza las bibliotecas compiladas que van incluidas
# en el paquete con el proyecto de Visual Studio

include_directories(

    libs/glew/include

    libs/glfw/include

    libs/glm/include

    libs/misc/include

    libs/stb_image/include

    ${CMAKE_SOURCE_DIR}/include
)

link_directories(
    libs/glew/lib

    libs/glfw/lib
)

link_libraries(
    glew32.lib
    glfw3dll.lib
    opengl32.lib
)
else()

# está lo de TPV1 no he mirado como es para linux así que si usas linux pues lo siento

# En otros sistemas operativos utiliza find_package
# para encontrar las bibliotecas instaladas aparte

# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_ttf REQUIRED)

include_directories(
        # ${SDL2_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
    )
# link_libraries(${SDL2_LIBRARIES})

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(PlantillaIG
# Archivo de código
    src/main.cpp

    src/Camera.cpp
    src/Entity.cpp
    src/IG1App.cpp
    src/Image.cpp
    src/Light.cpp
    src/Material.cpp
    src/Mesh.cpp
    src/Scene.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Viewport.cpp
)