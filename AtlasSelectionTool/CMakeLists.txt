cmake_minimum_required(VERSION 2.8)
 
project(AtlasSelectionTool)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

FIND_PACKAGE( OpenMP )
if(OPENMP_FOUND)
message("AtlasSelectionTool: OPENMP FOUND")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
 
add_executable(AtlasSelectionTool AtlasSelectionTool.cxx)
target_link_libraries(AtlasSelectionTool ${ITK_LIBRARIES})
INSTALL(TARGETS AtlasSelectionTool DESTINATION bin/)
