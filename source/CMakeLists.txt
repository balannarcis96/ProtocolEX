#################################################
# 		    ProtocolEx by Narcis96				#
#################################################

cmake_minimum_required (VERSION 3.8)

project ("ProtocolEx" VERSION 1.0.0)

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#We remove exceptions and rtti and we add 
#	-multiprocessor compilation (/MP) 
#	-latest c++ version(/std:c++latest) 
#	-intrinsic functions(/Oi) 
#	-favor speed (/Ot)
set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /std:c++latest /MP /Oi /Ot")

# Include sub-projects.

#Third Paty Libs
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty)

#Libs
add_subdirectory ("ProtocolEx")

#Executables
add_subdirectory ("Tests")