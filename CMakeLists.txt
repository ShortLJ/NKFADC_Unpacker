# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(ASGARD_Unpacker)

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
add_library(HitBuilder SHARED src/HitBuilder.cxx inc/HitBuilder.h inc/Global.h)
target_link_libraries(HitBuilder TimeSorter)

add_library(FVHit SHARED src/FVHit.cxx inc/FVHit.h inc/Global.h)
target_link_libraries(FVHit ${ROOT_LIBRARIES})
add_library(SegHit SHARED src/SegHit.cxx inc/SegHit.h inc/Global.h)
target_link_libraries(SegHit ${ROOT_LIBRARIES})
add_library(CryHit SHARED src/CryHit.cxx inc/CryHit.h inc/Global.h)
target_link_libraries(CryHit FVHit SegHit)
target_link_libraries(CryHit ${ROOT_LIBRARIES})
add_library(ASGARD_Event SHARED src/ASGARD_Event.cxx inc/ASGARD_Event.h inc/Global.h)
target_link_libraries(ASGARD_Event ${ROOT_LIBRARIES})
target_link_libraries(ASGARD_Event CryHit)




#---Create  a main program using the library
add_executable(ASGARD_Unpacker Unpacker.cpp)
target_link_libraries(ASGARD_Unpacker HitBuilder)
target_link_libraries(ASGARD_Unpacker ASGARD_Event)
target_link_libraries(ASGARD_Unpacker ${ROOT_LIBRARIES})

target_include_directories(ASGARD_Unpacker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
ROOT_GENERATE_DICTIONARY(Event_dict MODULE ASGARD_Unpacker LINKDEF EventLinkDef.h)
