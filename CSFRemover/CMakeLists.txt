cmake_minimum_required(VERSION 2.8)
 
project(CSFRemover)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 
add_executable(CSFRemover CSFRemover.cxx)
target_link_libraries(CSFRemover ${ITK_LIBRARIES})

INSTALL(TARGETS CSFRemover DESTINATION bin/)
