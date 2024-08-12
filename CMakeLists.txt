# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Skel_Unpacker)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO )

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
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

add_library(Det1Hit SHARED src/Det1Hit.cxx inc/Det1Hit.h inc/Global.h)
target_link_libraries(Det1Hit ${ROOT_LIBRARIES})
#add_library(Det2Hit SHARED src/Det2Hit.cxx inc/Det2Hit.h inc/Global.h)
#target_link_libraries(Det2Hit ${ROOT_LIBRARIES})
add_library(SingleHit SHARED src/SingleHit.cxx inc/SingleHit.h inc/Global.h)
target_link_libraries(SingleHit Det1Hit)
#target_link_libraries(SingleHit Det2Hit)
target_link_libraries(SingleHit ${ROOT_LIBRARIES})
add_library(Skel_Event SHARED src/Skel_Event.cxx inc/Skel_Event.h inc/Global.h)
target_link_libraries(Skel_Event ${ROOT_LIBRARIES})
target_link_libraries(Skel_Event SingleHit)




#---Create  a main program using the library
add_executable(Skel_Unpacker Unpacker.cpp)
target_link_libraries(Skel_Unpacker FileReader)
target_link_libraries(Skel_Unpacker TimeSorter)
target_link_libraries(Skel_Unpacker HitBuilder)
target_link_libraries(Skel_Unpacker Skel_Event)
target_link_libraries(Skel_Unpacker ${ROOT_LIBRARIES})

target_include_directories(Skel_Unpacker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
ROOT_GENERATE_DICTIONARY(G__SkelEventDict MODULE Skel_Unpacker LINKDEF ${PROJECT_SOURCE_DIR}/inc/EventLinkDef.h)
add_library(SkelEventDict SHARED ${PROJECT_SOURCE_DIR}/inc/Skel_Event.h G__SkelEventDict.cxx)




set(MAP_TXT
	det_map.txt
	DrawHist_peak_peak.c
	NKFADC_Skel.C
	NKFADC_Skel.h
)

foreach(_script ${MAP_TXT})
	configure_file(
			${PROJECT_SOURCE_DIR}/${_script}
			${PROJECT_BINARY_DIR}/${_script}
			COPYONLY
			)
endforeach()

install(TARGETS Skel_Unpacker DESTINATION bin)
install(TARGETS Sig LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)
install(TARGETS Det1Hit LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)
install(TARGETS SingleHit LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)
install(TARGETS Skel_Event LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)
install(TARGETS FileReader LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)
install(TARGETS TimeSorter LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)
install(TARGETS HitBuilder LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)

install(TARGETS SkelEventDict LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION inc)
install(FILES ${PROJECT_BINARY_DIR}/libSkel_Unpacker_rdict.pcm DESTINATION bin)
install(FILES ${PROJECT_BINARY_DIR}/libSkel_Unpacker.rootmap DESTINATION lib)
install(FILES ${MAP_TXT} DESTINATION .)
