#
# Proyecto CMake para las prácticas de TPV1
#

cmake_minimum_required(VERSION 3.15...3.30)

# Proyecto en C++
project(ProyectoSDL VERSION 1.0 LANGUAGES CXX)

# Selecciona la versión C++20 del estándar (sin extensiones)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Compila con la biblioteca SDL
if (CMAKE_HOST_WIN32)
	# Utiliza las bibliotecas compiladas que van incluidas
	# en el paquete con el proyecto de Visual Studio

	include_directories(
		SDL2/include
		SDL2_image/include
	)

	link_directories(
		SDL2/lib
		SDL2_image/lib
	)

	link_libraries(
		SDL2.lib
		SDL2main.lib
		SDL2_image.lib
	)
else()
	# En otros sistemas operativos utiliza find_package
	# para encontrar las bibliotecas instaladas aparte

	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)

	include_directories(${SDL2_INCLUDE_DIRS})
	link_libraries(${SDL2_LIBRARIES})
endif()

add_executable(ProyectoSDL
	# Archivo de código
	HolaSDL/main.cpp
)