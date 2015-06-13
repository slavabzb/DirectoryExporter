project( DirectoryExporter )

cmake_minimum_required( VERSION 2.8 )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( SRC_LIST
  main.cpp
  DirectoryExporter.cpp
  XmlWriter.cpp
)

add_executable( ${PROJECT_NAME} ${SRC_LIST} )

target_link_libraries( ${PROJECT_NAME} -lShlwapi )
