cmake_minimum_required(VERSION 2.8)
 
project(ITKSetupTest)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 
add_executable(ITKSetupTest ITKSetupTest.cxx)
 
if( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(ITKSetupTest ITKReview ${ITK_LIBRARIES})
else( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(ITKSetupTest ${ITK_LIBRARIES})
endif( "${ITK_VERSION_MAJOR}" LESS 4 )

#INSTALL(TARGETS ITKSetupTest DESTINATION bin/)
