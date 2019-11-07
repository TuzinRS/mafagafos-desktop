project (mypackage)
cmake_minimum_required (VERSION 3.1)
set (VERSION_MAJOR "1")
set (VERSION_MINOR "0")
set (VERSION_PATCH "2")
set (VERSION_BUILD "") # ie "-beta1", or empty string if release: ""
set (VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

#
# This approach to labeling beta versions is in line with Apple's
# inflexible versioning scheme for pre-release beta testing versions,
# for both iOS and macOS.  Apple allows, ie, FlightTest to release
# versions like "1.0.0b1" (b2,b2,...) as a pre-release beta for
# "1.0.0".  There is no other possible beta numbering scheme in Apple
# world, dont even bother trying! :D This labelling with "-beta2" or
# "" for releases also plays well with the other package generators.
#
if (VERSION_BUILD)
  string (REGEX MATCH "[0-9]+" VERSION_BUILD_NUM ${VERSION_BUILD})
else ()
  set (VERSION_BUILD_NUM "")
endif ()

#################################################################################
set (CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
if (APPLE AND NOT XCODE)
  set (CPACK_GENERATOR "DragNDrop;TGZ")
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
add_subdirectory (thirdparty EXCLUDE_FROM_ALL)

#################################################################################

add_executable (app MACOSX_BUNDLE WIN32 sdl2-app.cpp)
target_link_libraries (app SDL2-interface)

# everything else
install (TARGETS app
  BUNDLE DESTINATION "bin" COMPONENT App
  RUNTIME DESTINATION "bin" COMPONENT App
  )

#################################################################################

# CPack
set (CPACK_COMPONENTS_ALL App)

set (CPACK_PACKAGE_NAME "mypackage")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "sdl2 app package")
set (CPACK_PACKAGE_VERSION "${VERSION}${VERSION_BUILD}")
set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set (CPACK_PACKAGE_URL "http://sdl.org")
set (CPACK_PACKAGE_VENDOR "nobody")
set (CPACK_PACKAGE_CONTACT "nobody@nowhere")
set (CPACK_PACKAGE_RELOCATABLE TRUE)
set (CPACK_STRIP_FILES TRUE)
set (CPACK_SOURCE_STRIP_FILES TRUE)

# WIN32
if (WIN32)
  set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-install-win32")
  set (CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
  set (CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\sdl.org")
endif (WIN32)

# macOS
if (APPLE AND NOT XCODE)
  set (CPACK_GENERATOR "DragNDrop")
  set (CPACK_BUNDLE_NAME "${CPACK_PACKAGE_NAME}")
endif (APPLE AND NOT XCODE)

# unix
if (UNIX AND NOT APPLE)
  set (CPACK_GENERATOR "RPM;TGZ;DEB;STGZ")
  set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY 1)
  set (CPACK_VERBATIM_VARIABLES TRUE) # fixes @ in rpm file names
  set (CPACK_RPM_PACKAGE_RELEASE 1)
  set (CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
endif (UNIX AND NOT APPLE)

include (CPack)
