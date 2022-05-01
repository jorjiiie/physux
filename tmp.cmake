cmake_minimum_required(VERSION 3.14)
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
# add_executable(renderer src/test3.cpp src/glad.c src/gfx/RenderWindow.cpp)
add_executable(renderer src/test3.cpp)
target_link_libraries(renderer glfw glm ${EXTRA_LIBS})
