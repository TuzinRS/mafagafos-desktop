project (test1_thirdparty)
cmake_minimum_required (VERSION 3.1)
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)
include (ExternalProject)

set (SDL_VERSION 2.0.10)
set (SDL_VERSION_HASH 5a2114f2a6f348bdab5bf52b994811db)
get_directory_property (hasParent PARENT_DIRECTORY)

ExternalProject_Add (sdl2X
  PREFIX sdl2X
  URL https://www.libsdl.org/release/SDL2-${SDL_VERSION}.tar.gz
  URL_HASH "MD5=${SDL_VERSION_HASH}"
  DOWNLOAD_DIR "$ENV{HOME}/Downloads"
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON)
ExternalProject_Get_Property (sdl2X source_dir)

if (hasParent)
  set (SDL_STATIC ON CACHE BOOL "" FORCE)
  set (SDL_STATIC_PIC ON CACHE BOOL "" FORCE)
  set (SDL_SHARED OFF CACHE BOOL "" FORCE)
  add_subdirectory ("${source_dir}" "${CMAKE_CURRENT_BINARY_DIR}/sdl2X")

  find_package (OpenGL REQUIRED)

  cmake_policy (SET CMP0079 NEW)
  if (SDL_SHARED)
    target_link_libraries(SDL2 OpenGL::GL)
  endif (SDL_SHARED)
  if (SDL_STATIC)
    target_link_libraries(SDL2-static OpenGL::GL)
  endif (SDL_STATIC)

endif (hasParent)
