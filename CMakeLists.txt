
# 参考: https://github.com/aminosbh/sdl2-image-sample

set(CMAKE_CXX_STANDARD 17)


# Define the project name
project(fill_tiles)

# Set the cmake minimum version to 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)


# Enable ExternalProject
include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)


# Download and build lua
ExternalProject_Add(
        lua-ext
        GIT_REPOSITORY https://github.com/LuaDist/lua.git
        GIT_TAG master
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DBUILD_SHARED_LIBS=OFF
)

ADD_LIBRARY(lua IMPORTED STATIC)
SET_TARGET_PROPERTIES(lua PROPERTIES IMPORTED_LOCATION ${EXTERNAL_INSTALL_LOCATION}/lib/liblua.a)
ADD_DEPENDENCIES(lua lua-ext)


# Set Cmake modules
set(Boost_NO_BOOST_CMAKE ON)
set(BOOST_ROOT "/home/sashi/boost_1_79_0")
set(Boost_INCLUDE_DIR ${BOOST_ROOT}/include)
set(Boost_LIBRARY_DIR ${BOOST_ROOT}/lib)
find_package(Boost COMPONENTS context REQUIRED)

set(cpplinq_INCLUDE_DIR "/home/sashi/RxCpp-4.1.1/Ix/CPP/src")
set(RxCpp_INCLUDE_DIR "/home/sashi/RxCpp-4.1.1/Rx/v2/src")


# Add all cpp source files under the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
#target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${RxCpp_INCLUDE_DIR}
        ${cpplinq_INCLUDE_DIR}
        include)

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror> -DLUA_LIBRARY=/usr/local/lib/liblua.a\;/usr/lib/libdl.so)


# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
#find_package(SDL2_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::GFX)

# Add Boost library
target_link_libraries(${PROJECT_NAME} Boost::boost Boost::context)

# Link Lua
target_link_libraries(${PROJECT_NAME} m dl lua)

# Copy assets
#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
