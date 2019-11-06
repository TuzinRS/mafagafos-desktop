project (mypackage)
cmake_minimum_required (VERSION 3.1)
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

#################################################################################
set (CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
if (APPLE AND NOT XCODE)
  set (CPACK_GENERATOR "DragNDrop")
endif (APPLE AND NOT XCODE)

#################################################################################
#
# Build external dependencies
#
#file (REMOVE_RECURSE "${CMAKE_BINARY_DIR}/thirdparty")
file (MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/thirdparty")
message ("Created ${CMAKE_BINARY_DIR}/thirdparty")

# generator name
if (NOT "${CMAKE_EXTRA_GENERATOR}" STREQUAL "")
  set (GENERATOR_STRING "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else ()
  set (GENERATOR_STRING "${CMAKE_GENERATOR}")
endif ()

# configure the thirdparty build dir
execute_process (
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/thirdparty"
  COMMAND ${CMAKE_COMMAND} -G${GENERATOR_STRING} "-DCMAKE_CONFIGURATION_TYPES=${CMAKE_CONFIGURATION_TYPES}" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM} ${CMAKE_SOURCE_DIR}/thirdparty
  RESULT_VARIABLE THIRDPARTY_CONFIG_RESULT
  )
if (THIRDPARTY_CONFIG_RESULT)
  message (FATAL_ERROR "Configuring dependencies failed: ${THIRDPARTY_CONFIG_RESULT}")
endif ()

# build the thirdparty
message ("********** Building: '${CMAKE_BINARY_DIR}/thirdparty' ***********")
execute_process (
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/thirdparty"
  COMMAND "${CMAKE_COMMAND}" --build .
  RESULT_VARIABLE THIRDPARTY_BUILD_RESULT
  )
message ("Building thirdparty/ done.")
if (THIRDPARTY_BUILD_RESULT)
  message (FATAL_ERROR "Building dependencies failed: ${THIRDPARTY_BUILD_RESULT}")
endif ()

# import the thirdparty's location variables
add_subdirectory (thirdparty)

#################################################################################

add_executable (app MACOSX_BUNDLE WIN32 sdl2-app.cpp)
target_link_libraries (app SDL2-interface)

# everything else
install (TARGETS app
  BUNDLE DESTINATION "bin" COMPONENT App
  RUNTIME DESTINATION "bin" COMPONENT App
  )

#################################################################################

set (CPACK_COMPONENTS_ALL App)
include (CPack)
