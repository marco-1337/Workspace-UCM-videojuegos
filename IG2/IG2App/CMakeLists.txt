cmake_minimum_required(VERSION 3.10.0)
project(IG2App VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OGRE_SDK $ENV{OGRE_DEBUG})

set(OGRE_DIR ${OGRE_SDK}/sdk/CMake)
set(SDL2_DIR ${OGRE_SDK}/Dependencies/cmake)

# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
find_package(SDL2 REQUIRED)

add_executable(IG2App 
    Main.cpp
    IG2App.cpp)

target_include_directories(IG2App PRIVATE
    ${CMAKE_SOURCE_DIR})

# this also sets the includes and pulls third party dependencies
target_link_libraries(IG2App PRIVATE
    OgreMain
    OgreBites
    SDL2::SDL2
    SDL2::SDL2main
    )

set_target_properties(IG2App PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)


# Ruta OGRE bin y media (desde variable de entorno)
set(OGRE_BINDIR ${OGRE_SDK}/sdk/bin)
# Copy DLLs to target bin
file(GLOB OGRE_DLL_FILES "${OGRE_BINDIR}/*.dll")

# Copy dlls into bin
foreach(dll_file IN LISTS OGRE_DLL_FILES)
    get_filename_component(dll_name ${dll_file} NAME)
    add_custom_command(TARGET IG2App POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${dll_file} $<TARGET_FILE_DIR:IG2App>/${dll_name}
        COMMENT "Copiando DLL: ${dll_name}"
    )
endforeach()