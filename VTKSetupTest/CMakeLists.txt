cmake_minimum_required(VERSION 2.8)
 
PROJECT(VTKSetupTest)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VTKSetupTest VTKSetupTest)
 
if(VTK_LIBRARIES)
  target_link_libraries(VTKSetupTest ${VTK_LIBRARIES})
endif()

INSTALL(TARGETS VTKSetupTest DESTINATION bin/)

