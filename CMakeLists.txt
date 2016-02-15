# Require at least cmake 2.6.0
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# Name of this project
project(QweakSimG4)

# Find Geant4
SITE_NAME(mySite)
if(${mySite} MATCHES "ifarm*")
   set(Geant4_DIR /lustre/expphy/work/hallc/qweak/ciprian/geant41001p02/geant4.10.01.p02/build)
#   set(Geant4_DIR /w/hallc-scifs2/qweak/ciprian/geant41001p01/source/geant4.10.01.p01/build)
#   set(Geant4_DIR $ENV{G4INSTALL}/build)	
   message( "On ifarm using custom geant4_dir: " ${Geant4_DIR})
   find_package(Geant4 REQUIRED COMPONENTS gdml qt ui_all vis_all)
   execute_process(COMMAND ${Geant4_DIR}/geant4-config --version
                   OUTPUT_VARIABLE GEANT4_VERSION
                   OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
   if(NOT DEFINED Geant4_DIR)
	set(Geant4_DIR $ENV{G4INSTALL}/build)
   endif(NOT DEFINED Geant4_DIR)
   find_package(Geant4 REQUIRED COMPONENTS gdml qt ui_all vis_all)
   execute_process(COMMAND geant4-config --version
                   OUTPUT_VARIABLE GEANT4_VERSION
                   OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

message(STATUS "Found Geant4 ${GEANT4_VERSION}")

# Add the project include directory and put all source files in my_project_sources
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
if(GEANT4_VERSION VERSION_LESS "10.0.0")
       message(STATUS "Geant4 is < 10.0.0: skip building custom physics processes")
       file(GLOB my_project_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
else(GEANT4_VERSION VERSION_LESS "10.0.0")
       message(STATUS "Geant4 > 10.0.0: include building custom physics processes")
       file(GLOB_RECURSE my_project_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
endif(GEANT4_VERSION VERSION_LESS "10.0.0")


# Explicitly add compiler flag -fPIC as required by geant4.10 on ifarm65
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# Local path for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Custom target that is always built
#add_custom_target(QweakSimVersion ALL)
# Creates QweakSimVersion.hh using cmake script
#add_custom_command(TARGET QweakSimVersion
#	COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
#	-P ${CMAKE_CURRENT_SOURCE_DIR}/GetQweakSimVersion.cmake)
# QweakSimVersion.hh is a generated file
#set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/QweakSimVersion.h
#	PROPERTIES GENERATED TRUE
#	HEADER_FILE_ONLY TRUE)

#MAC specific variable
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
    if("${isSystemDir}" STREQUAL "-1")
        set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    endif()
endif()

# Update header file
add_custom_target( gitinfo ALL COMMAND ${PROJECT_SOURCE_DIR}/pullgitinfo.py ${PROJECT_SOURCE_DIR} COMMENT "Creating gitinfo.hh" )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Load ROOT and setup include directory
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

# Create ROOT dictionary before messing up include dirs with Geant4 stuff
# (-p option to "use of the compiler's preprocessor instead of CINT's preprocessor.")
ROOT_GENERATE_DICTIONARY(${CMAKE_CURRENT_BINARY_DIR}/QweakSimDict
	${CMAKE_CURRENT_SOURCE_DIR}/include/QweakSimUser*Event.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/QweakSimUser*Config.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/QweakSimUserRunInformation.hh
	LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/QweakSimLinkDef.hh
	OPTIONS -p)
set(my_project_sources ${my_project_sources} ${CMAKE_CURRENT_BINARY_DIR}/QweakSimDict.cxx)

# Load Geant4 through Find and Use files
include(${Geant4_USE_FILE})

# Link the ROOT and Geant4 libraries
add_library(QweakSim SHARED ${my_project_sources})
#add_dependencies(QweakSim QweakSimVersion)
target_link_libraries(QweakSim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

# Add the target executables:
# - QweakSimG4
add_executable(QweakSimG4 QweakSimG4.cc)
target_link_libraries(QweakSimG4 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - QweakSimRoot
add_executable(QweakSimRoot QweakSimRoot.cc)
target_link_libraries(QweakSimRoot ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - QweakAna
add_executable(QweakAna QweakAna.cc)
target_link_libraries(QweakAna ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - QweakCalcPMTDD
add_executable(QweakCalcPMTDD QweakCalcPMTDD.cc)
target_link_libraries(QweakCalcPMTDD ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - QweakAnaPEs
add_executable(QweakAnaPEs QweakAnaPEs.cc)
target_link_libraries(QweakAnaPEs ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - QweakTreeStrip
add_executable(QweakTreeStrip QweakTreeStrip.cc)
target_link_libraries(QweakTreeStrip ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - DrawMSAn
add_executable(DrawMSAn DrawMSAn.cc)
target_link_libraries(DrawMSAn ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - QweakGetPEs
add_executable(QweakGetPEs QweakGetPEs.cc)
target_link_libraries(QweakGetPEs ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)
# - QweakPowerAna
add_executable(QweakPowerAna QweakPowerAna.cc)
target_link_libraries(QweakPowerAna ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QweakSim)

