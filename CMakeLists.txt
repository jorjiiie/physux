cmake_minimum_required(VERSION 3.8)
project(Renderer)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

include_directories(lib)
include_directories(lib/glad)
# include(lib/linmath.h)

add_definitions(-DGL_SILENCE_DEPRECATION)

if (APPLE) 
    list(APPEND EXTRA_LIBS
        "-framework OpenGL"
    )

elseif(WIN32)
    list(APPEND EXTRA_LIBS
        "-lglu32 -lopengl32"
    )
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else()
    list(APPEND EXTRA_LIBS
        "-lGL -lGLU -lX11"
    )
endif()

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()



add_compile_options(-Wno-unused)
add_compile_options(-Wno-unused-parameter)

file (GLOB_RECURSE R_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE R_HEADER CONFIGURE_DEPENDS "src/*.h")

set (R_INCLUDE_DIRS "")
foreach (_headerFile ${R_HEADER})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND R_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES R_INCLUDE_DIRS)
message(STATUS "sources: ${R_SOURCES}")
message(STATUS "headers: ${R_HEADER}")

add_executable(renderer ${R_SOURCES} lib/glad/glad/glad.c)

target_compile_features(renderer PUBLIC cxx_std_17)

target_link_libraries(renderer glfw glm ${EXTRA_LIBS})

target_include_directories(renderer PRIVATE ${R_INCLUDE_DIRS})

