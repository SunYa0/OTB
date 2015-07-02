set(proj PACKAGE-OTB)

if(NOT __EXTERNAL_${proj}__)
set(__EXTERNAL_${proj}__ 1)

message(STATUS "Setup OTB Packaging...")

SETUP_SUPERBUILD(PROJECT ${proj})

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/${proj}/src/")

# declare dependencies
#set(${proj}_DEPENDENCIES OTB)
#INCLUDE_SUPERBUILD_DEPENDENCIES(${${proj}_DEPENDENCIES})

#message(FATAL_ERROR "PACKAGE_SB_BUILD_DIR=${PACKAGE_SB_BUILD_DIR}")


ExternalProject_Add(${proj}
  PREFIX ${proj}
  SOURCE_DIR ${PACKAGE-OTB_SB_SRC_DIR}
  BINARY_DIR ${PACKAGE-OTB_SB_BUILD_DIR}
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_COMMAND ""
  CMAKE_CACHE_ARGS
  -DCMAKE_INSTALL_PREFIX:STRING=${SB_INSTALL_PREFIX}
  -DCMAKE_BUILD_TYPE:STRING=Release
  CMAKE_COMMAND ${SB_CMAKE_COMMAND}
  DEPENDS OTB)

# ExternalProject_Add_Step(${proj} set_rpath
#   COMMAND ${PATCHELF_PROGRAM} "--set-rpath" "../lib" ""
#   DEPENDEES install)


endif()
