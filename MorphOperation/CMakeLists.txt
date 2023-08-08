cmake_minimum_required(VERSION 2.8)
 
project(MorphOperation)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

IF(WIN32)
	add_executable(MorphOperation ../util/XGetopt.cpp MorphOperation.cxx)
ELSE(WIN32)
	add_executable(MorphOperation MorphOperation.cxx)
ENDIF(WIN32)

target_link_libraries(MorphOperation ${ITK_LIBRARIES})

INSTALL(TARGETS MorphOperation DESTINATION bin/)
