cmake_minimum_required( VERSION 3.30.2)

project( 3DRenderer LANGUAGES CXX)

find_package(Catch2 3 REQUIRED)


# Set to C++17
set( CMAKE_CXX_STANDARD             17)
set( CMAKE_CXX_STANDARD_REQUIRED    ON)
set( CMAKE_CXX_EXTENSIONS           OFF)


set( SOURCE
    src/canvas.cc
    src/color.cc
    src/scene.cc
    src/sphere.cc
    src/vec3.cc
    )
set( SOURCE_RASTERIZER
    "")
set( SOURCE_RAYTRACER 
    src/Raytracer/raytracer.cc
    src/Raytracer/main.cc
)

set( SOURCE_TESTS
    tests/test_vec3.cc
    tests/test_color.cc
)

include_directories(src)


message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # /wd #### - Disable warning
    # /we #### - treat warning as error
    add_compile_options("/W4")      # Enable level-4 warnings
    add_compile_options("/we 4265") # Class has virtual functions, but its non-trivial destructor is not virtual
    add_compile_options("/we 5204") # Class has virtual functions, but its trivial destructor is not virtual
    add_compile_options("/wd 4100") # unreferenced formal parameter
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wmaybe-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
    add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
    add_compile_options(-Wsometimes-uninitialized) # Variable improperly initialized
    add_compile_options(-Wunused-variable) # Variable is defined but unused
endif()

# Add executables
add_executable(Raytracer    ${SOURCE} ${SOURCE_RAYTRACER})
#add_executable(Rasterizer   ${SOURCE} ${SOURCE_RASTERIZER})
add_executable(tests ${SOURCE} ${SOURCE_TESTS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(tests PRIVATE Catch2::Catch2)

