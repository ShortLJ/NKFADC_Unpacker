# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(NaI_Unpacker)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO )

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
#ROOT_GENERATE_DICTIONARY(G__Sig Sig.h LINKDEF SigLinkDef.h)
#ROOT_GENERATE_DICTIONARY(G__TimeSorter TimeSorter.h LINKDEF TimeSorterLinkDef.h)
#ROOT_GENERATE_DICTIONARY(G__Hit Hit.h LINKDEF HitLinkDef.h)


#---Create a shared library with geneated dictionary
add_library(Sig SHARED src/Sig.cxx inc/Sig.h)

add_library(TimeSorter SHARED src/TimeSorter.cxx inc/TimeSorter.h inc/Global.h)
target_link_libraries(TimeSorter Sig)
add_library(FileReader SHARED src/FileReader.cxx inc/FileReader.h inc/Global.h)
target_link_libraries(FileReader Sig TimeSorter)
add_library(HitBuilder SHARED src/HitBuilder.cxx inc/HitBuilder.h inc/Global.h)
target_link_libraries(HitBuilder TimeSorter)

add_library(NaIHit SHARED src/NaIHit.cxx inc/NaIHit.h inc/Global.h)
target_link_libraries(NaIHit Sig)
target_link_libraries(NaIHit ${ROOT_LIBRARIES})
add_library(NaI_Event SHARED src/NaI_Event.cxx inc/NaI_Event.h inc/Global.h)
target_link_libraries(NaI_Event ${ROOT_LIBRARIES})
target_link_libraries(NaI_Event NaIHit)




#---Create  a main program using the library
add_executable(NaI_Unpacker Unpacker.cpp)
target_link_libraries(NaI_Unpacker FileReader)
target_link_libraries(NaI_Unpacker HitBuilder)
target_link_libraries(NaI_Unpacker NaI_Event)
target_link_libraries(NaI_Unpacker ${ROOT_LIBRARIES})

target_include_directories(NaI_Unpacker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
ROOT_GENERATE_DICTIONARY(Event_dict MODULE NaI_Unpacker LINKDEF EventLinkDef.h)
add_library(NaIEvent_dict SHARED ${PROJECT_SOURCE_DIR}/inc/NaI_Event.h  Event_dict.cxx)
