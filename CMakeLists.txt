cmake_minimum_required(VERSION 3.15)

project(
  matrix-simple
  DESCRIPTION "Schönherz Mátrix super module"
  HOMEPAGE_URL "kszk.bme.hu"
  LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(libmueb)
add_subdirectory(emu)
add_subdirectory(animsource)
add_subdirectory(colorsource)
add_subdirectory(drawsource)
add_subdirectory(percentsource)
add_subdirectory(windowtestsource)
add_subdirectory(q4x-extractor)
