# Archivo de configuración standard para CMake

cmake_minimum_required(VERSION 3.15...3.30)

# Proyecto en C++
project(IG1_Practicas VERSION 1.0 LANGUAGES CXX)

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

# En otros sistemas operativos utiliza find_package
# para encontrar las bibliotecas instaladas aparte

    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)

    include_directories(
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
    )

    set(LIBS ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
    target_link_libraries(IG1_Practicas ${LIBS})
    
endif()

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/Entities/
)

add_executable(IG1_Practicas
# Archivo de código
    src/main.cpp

    src/Camera.cpp
    src/Entities/Entity.cpp
    src/IG1App.cpp
    src/Image.cpp
    src/Light.cpp
    src/Material.cpp
    src/Mesh.cpp
    src/Scene.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Viewport.cpp

    #Práctica 1
    src/Entities/SingleColorEntity.cpp
    src/Entities/RegularPolygon.cpp
    src/Entities/RGBTriangle.cpp
    src/Entities/RGBRectangle.cpp
    src/Entities/Cube.cpp
    src/Entities/RGBCube.cpp

    #práctica 2
    src/Entities/EntityWithTexture.cpp
    src/Entities/Ground.cpp
    src/Entities/BoxOutline.cpp
    src/Entities/Star3D.cpp
    src/Entities/Box.cpp
    src/Entities/GlassParapet.cpp
    src/Entities/Photo.cpp

    #práctica 4
    src/IndexMesh.cpp
    src/Entities/Torus.cpp
    src/Entities/ColorMaterialEntity.cpp
    src/Entities/IndexedBox.cpp
    src/Entities/Sphere.cpp
    src/Entities/Disk.cpp
    src/Entities/Cone.cpp
    src/Entities/CompoundEntity.cpp
    src/Entities/WingAdvancedTIE.cpp
    src/Entities/TranslucentEntity.cpp
    src/Entities/AdvancedTIE.cpp

    src/Scene0.cpp
    src/Scene1.cpp
    src/Scene2.cpp
    src/Scene3.cpp
    src/Scene4.cpp
    src/Scene5.cpp
    src/Scene6.cpp
    src/Scene7.cpp
)

set_target_properties(IG1_Practicas PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)

set(DLL_DIR ${CMAKE_SOURCE_DIR}/dlls)

add_custom_command(TARGET IG1_Practicas POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${DLL_DIR} $<TARGET_FILE_DIR:IG1_Practicas>
)