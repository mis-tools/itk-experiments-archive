cmake_minimum_required(VERSION 2.8)
 
project(LabelMapComparator)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 
add_executable(LabelMapCombiner LabelMapCombiner.cxx)
 
if( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(LabelMapCombiner ITKReview ${ITK_LIBRARIES})
else( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(LabelMapCombiner ${ITK_LIBRARIES})
endif( "${ITK_VERSION_MAJOR}" LESS 4 )

INSTALL(TARGETS LabelMapCombiner DESTINATION bin/)
