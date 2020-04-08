cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(LightGathering CXX)

option(WITH_GEANT4_UIVIS "Build Geant4 with UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc)

file(GLOB sources CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/inc/*.hh)

add_executable(LightGathering main.cc ${sources} ${headers})
target_link_libraries(LightGathering ${Geant4_LIBRARIES})

configure_file(${PROJECT_SOURCE_DIR}/init_vis.mac ${PROJECT_BINARY_DIR}/init_vis.mac COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/vis.mac ${PROJECT_BINARY_DIR}/vis.mac COPYONLY)