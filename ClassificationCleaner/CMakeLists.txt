cmake_minimum_required(VERSION 2.8)
 
project(ClassificationCleaner)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
 
add_executable(ClassificationCleaner ClassificationCleaner.cxx)
target_link_libraries(ClassificationCleaner ${ITK_LIBRARIES})

INSTALL(TARGETS ClassificationCleaner DESTINATION bin/)
